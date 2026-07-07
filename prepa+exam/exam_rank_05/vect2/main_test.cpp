#include "vect2.hpp"
#include <iostream>
#include <sstream>

static int g_pass = 0;
static int g_fail = 0;

void check(const std::string &test, const vect2 &got, int ex, int ey) {
	if (got[0] == ex && got[1] == ey) {
		std::cout << "✅ " << test << " = " << got << std::endl;
		++g_pass;
	} else {
		std::cout << "❌ " << test << " got " << got << " expected {" << ex << ", " << ey << "}" << std::endl;
		++g_fail;
	}
}

void check_bool(const std::string &test, bool got, bool expected) {
	if (got == expected) {
		std::cout << "✅ " << test << " = " << got << std::endl;
		++g_pass;
	} else {
		std::cout << "❌ " << test << " got " << got << " expected " << expected << std::endl;
		++g_fail;
	}
}

int main() {
	std::cout << "=== Constructeurs ===" << std::endl;
	vect2 a;
	check("default ctor", a, 0, 0);
	vect2 b(3, 7);
	check("int ctor", b, 3, 7);
	vect2 c(b);
	check("copy ctor", c, 3, 7);
	vect2 d = b;
	check("copy assign ctor", d, 3, 7);

	std::cout << "\n=== Assignation ===" << std::endl;
	vect2 e;
	e = b;
	check("operator=", e, 3, 7);

	std::cout << "\n=== operator[] ===" << std::endl;
	check_bool("b[0] == 3", b[0] == 3, true);
	check_bool("b[1] == 7", b[1] == 7, true);
	const vect2 cb(5, 9);
	check_bool("const cb[0] == 5", cb[0] == 5, true);
	check_bool("const cb[1] == 9", cb[1] == 9, true);
	vect2 f(1, 2);
	f[0] = 10;
	f[1] = 20;
	check("f[0]=10 f[1]=20", f, 10, 20);

	std::cout << "\n=== Pre/Post increment ===" << std::endl;
	vect2 g(1, 2);
	check("g++ retourne", g++, 1, 2);
	check("g++ apres", g, 2, 3);
	check("++g retourne", ++g, 3, 4);
	check("++g apres", g, 3, 4);

	std::cout << "\n=== Pre/Post decrement ===" << std::endl;
	vect2 h(3, 4);
	check("h-- retourne", h--, 3, 4);
	check("h-- apres", h, 2, 3);
	check("--h retourne", --h, 1, 2);
	check("--h apres", h, 1, 2);

	std::cout << "\n=== Addition ===" << std::endl;
	check("(1,2)+(3,4)", vect2(1,2)+vect2(3,4), 4, 6);
	check("(0,0)+(0,0)", vect2(0,0)+vect2(0,0), 0, 0);
	check("(1,2)+3", vect2(1,2)+3, 4, 5);
	check("3+(1,2)", 3+vect2(1,2), 4, 5);
	vect2 i(1, 2);
	i += vect2(3, 4);
	check("(1,2) += (3,4)", i, 4, 6);
	i += 10;
	check("(4,6) += 10", i, 14, 16);

	std::cout << "\n=== Soustraction ===" << std::endl;
	check("(5,9)-(2,3)", vect2(5,9)-vect2(2,3), 3, 6);
	check("(1,2)-1", vect2(1,2)-1, 0, 1);
	check("10-(3,4)", 10-vect2(3,4), 7, 6);
	vect2 j(10, 20);
	j -= vect2(3, 5);
	check("(10,20) -= (3,5)", j, 7, 15);
	j -= 2;
	check("(7,15) -= 2", j, 5, 13);

	std::cout << "\n=== Multiplication ===" << std::endl;
	check("(2,3)*4", vect2(2,3)*4, 8, 12);
	check("4*(2,3)", 4*vect2(2,3), 8, 12);
	check("(2,3)*(4,5)", vect2(2,3)*vect2(4,5), 8, 15);
	vect2 k(2, 3);
	k *= 5;
	check("(2,3) *= 5", k, 10, 15);
	k *= vect2(2, 2);
	check("(10,15) *= (2,2)", k, 20, 30);

	std::cout << "\n=== Unaire - ===" << std::endl;
	check("-(2,3)", -vect2(2,3), -2, -3);
	check("-(0,0)", -vect2(0,0), 0, 0);
	check("-(-5,7)", -vect2(-5,7), 5, -7);

	std::cout << "\n=== Comparaisons ===" << std::endl;
	check_bool("(1,2)==(1,2)", vect2(1,2)==vect2(1,2), true);
	check_bool("(1,2)==(1,3)", vect2(1,2)==vect2(1,3), false);
	check_bool("(1,2)!=(1,3)", vect2(1,2)!=vect2(1,3), true);
	check_bool("(1,2)!=(1,2)", vect2(1,2)!=vect2(1,2), false);

	std::cout << "\n=== operator<< ===" << std::endl;
	std::ostringstream oss;
	oss << vect2(4, 8);
	check_bool("cout << vect2(4,8)", oss.str() == "{4, 8}", true);

	std::cout << "\n=== Tests batards ===" << std::endl;

	// Self assign
	vect2 sa(5, 10);
	vect2 &sa_ref = sa;
	sa = sa_ref;
	check("self = self", sa, 5, 10);

	// v1 = v1 - v1 + v1
	vect2 sb(3, 6);
	sb = sb - sb + sb;
	check("v = v - v + v", sb, 3, 6);

	// Chaine += 
	vect2 sc(1, 2);
	const vect2 sc2(1, 2);
	sc += sc += sc2;
	check("v += v += v2", sc, 4, 8);

	// Negatif puis multiplication
	vect2 sd(2, 4);
	sd *= 42;
	check("(2,4) *= 42", sd, 84, 168);
	sd = -sd;
	check("-(84,168)", sd, -84, -168);

	// Increment/decrement sur negatif
	vect2 se(-1, -1);
	check("++(-1,-1)", ++se, 0, 0);
	check("--( 0, 0)", --se, -1, -1);

	// operator+ ne modifie pas les operandes
	vect2 sf(10, 20);
	vect2 sg(5, 5);
	vect2 sh = sf + sg;
	check("10+5, 20+5", sh, 15, 25);
	check("sf inchange", sf, 10, 20);
	check("sg inchange", sg, 5, 5);

	std::cout << "\n=== Resultat ===" << std::endl;
	std::cout << g_pass << " passed, " << g_fail << " failed" << std::endl;
	return g_fail > 0 ? 1 : 0;
}
