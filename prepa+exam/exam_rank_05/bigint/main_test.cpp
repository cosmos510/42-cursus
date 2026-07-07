#include "test.hpp"
#include <iostream>

static int g_pass = 0;
static int g_fail = 0;

void check(const std::string &test, const bigint &got, const std::string &expected) {
	if (got.getNbr() == expected) {
		std::cout << "✅ " << test << " = " << got << std::endl;
		++g_pass;
	} else {
		std::cout << "❌ " << test << " got " << got << " expected " << expected << std::endl;
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
	bigint a;
	check("default ctor", a, "0");
	bigint b(42);
	check("int ctor", b, "42");
	bigint c(b);
	check("copy ctor", c, "42");
	bigint d(0);
	check("zero ctor", d, "0");
	bigint e(4294967295u);
	check("UINT_MAX ctor", e, "4294967295");

	std::cout << "\n=== Assignation ===" << std::endl;
	bigint f;
	f = b;
	check("operator=", f, "42");
	f = bigint(0);
	check("assign 0", f, "0");

	std::cout << "\n=== Addition ===" << std::endl;
	check("42 + 0", bigint(42) + bigint(0), "42");
	check("0 + 0", bigint(0) + bigint(0), "0");
	check("0 + 42", bigint(0) + bigint(42), "42");
	check("1 + 9", bigint(1) + bigint(9), "10");
	check("99 + 1", bigint(99) + bigint(1), "100");
	check("999 + 1", bigint(999) + bigint(1), "1000");
	check("123 + 456", bigint(123) + bigint(456), "579");
	check("999999 + 1", bigint(999999) + bigint(1), "1000000");
	// gros nombres
	bigint big1(4294967295u);
	bigint big2(4294967295u);
	check("UINT_MAX + UINT_MAX", big1 + big2, "8589934590");

	std::cout << "\n=== operator+= ===" << std::endl;
	bigint g(100);
	g += bigint(50);
	check("100 += 50", g, "150");
	g += bigint(0);
	check("150 += 0", g, "150");
	bigint h(0);
	h += bigint(0);
	check("0 += 0", h, "0");

	std::cout << "\n=== Incrementation ===" << std::endl;
	bigint i(9);
	check("++9", ++i, "10");
	check("apres ++", i, "10");
	bigint j(99);
	bigint j_old = j++;
	check("99++ retourne", j_old, "99");
	check("99++ apres", j, "100");
	bigint k(0);
	check("++0", ++k, "1");

	std::cout << "\n=== Left shift (<<) ===" << std::endl;
	check("42 << 0", bigint(42) << 0u, "42");
	check("42 << 1", bigint(42) << 1u, "420");
	check("42 << 3", bigint(42) << 3u, "42000");
	check("0 << 5", bigint(0) << 5u, "0");
	check("1 << 10", bigint(1) << 10u, "10000000000");
	// avec bigint shift
	check("42 << bigint(2)", bigint(42) << bigint(2), "4200");
	check("0 << bigint(3)", bigint(0) << bigint(3), "0");

	std::cout << "\n=== Left shift assign (<<= ) ===" << std::endl;
	bigint l(5);
	l <<= 3u;
	check("5 <<= 3", l, "5000");
	l <<= bigint(0);
	check("5000 <<= 0", l, "5000");

	std::cout << "\n=== Right shift (>>) ===" << std::endl;
	check("12345 >> 0", bigint(12345) >> 0u, "12345");
	check("12345 >> 2", bigint(12345) >> 2u, "123");
	check("12345 >> 5", bigint(12345) >> 5u, "0");
	check("12345 >> 10", bigint(12345) >> 10u, "0");
	check("0 >> 3", bigint(0) >> 3u, "0");
	// avec bigint shift
	check("12345 >> bigint(3)", bigint(12345) >> bigint(3), "12");

	std::cout << "\n=== Right shift assign (>>=) ===" << std::endl;
	bigint m(9876543);
	m >>= 3u;
	check("9876543 >>= 3", m, "9876");
	m >>= bigint(0);
	check("9876 >>= 0", m, "9876");
	m >>= 100u;
	check("9876 >>= 100", m, "0");

	std::cout << "\n=== Comparaisons ===" << std::endl;
	check_bool("42 == 42", bigint(42) == bigint(42), true);
	check_bool("42 == 43", bigint(42) == bigint(43), false);
	check_bool("42 != 43", bigint(42) != bigint(43), true);
	check_bool("42 != 42", bigint(42) != bigint(42), false);
	check_bool("42 < 43", bigint(42) < bigint(43), true);
	check_bool("43 < 42", bigint(43) < bigint(42), false);
	check_bool("42 < 42", bigint(42) < bigint(42), false);
	check_bool("100 < 99", bigint(100) < bigint(99), false);
	check_bool("99 < 100", bigint(99) < bigint(100), true);
	check_bool("42 > 41", bigint(42) > bigint(41), true);
	check_bool("42 > 42", bigint(42) > bigint(42), false);
	check_bool("42 <= 42", bigint(42) <= bigint(42), true);
	check_bool("42 <= 43", bigint(42) <= bigint(43), true);
	check_bool("43 <= 42", bigint(43) <= bigint(42), false);
	check_bool("42 >= 42", bigint(42) >= bigint(42), true);
	check_bool("43 >= 42", bigint(43) >= bigint(42), true);
	check_bool("42 >= 43", bigint(42) >= bigint(43), false);
	// tailles differentes
	check_bool("9 < 10", bigint(9) < bigint(10), true);
	check_bool("10 > 9", bigint(10) > bigint(9), true);
	check_bool("0 == 0", bigint(0) == bigint(0), true);

	std::cout << "\n=== Combinaisons ===" << std::endl;
	bigint n(1);
	for (int x = 0; x < 20; ++x)
		n += n;  // double 20 fois: 1 -> 1048576
	check("1 double 20 fois", n, "1048576");

	bigint o(99);
	o++;
	check("99++ puis valeur", o, "100");
	o += bigint(900);
	check("100 + 900", o, "1000");
	o >>= 2u;
	check("1000 >>= 2", o, "10");
	o <<= 5u;
	check("10 <<= 5", o, "1000000");

	std::cout << "\n=== Tests batards ==" << std::endl;

	// Self-addition: a += a
	bigint sa(12345);
	sa += sa;
	check("self += self (12345)", sa, "24690");

	// Self-assign
	bigint sb(777);
	bigint &sb_ref = sb;
	sb = sb_ref;
	check("self = self", sb, "777");

	// Chaine d'additions avec retenues max
	bigint sc(999999999);
	sc += bigint(999999999);
	sc += bigint(999999999);
	sc += bigint(999999999);
	check("999999999 * 4", sc, "3999999996");

	// Addition qui fait exploser la taille
	bigint sd(999999999);
	sd += bigint(1);
	check("999999999 + 1", sd, "1000000000");

	// Shift puis addition
	bigint se(1);
	se <<= 20u;
	se += bigint(1);
	check("1<<20 + 1", se, "100000000000000000001");

	// Right shift qui vide tout
	bigint sf(1);
	sf >>= 1u;
	check("1 >>= 1", sf, "0");

	// Shift 0 sur 0
	bigint sg(0);
	sg <<= 999u;
	check("0 <<= 999", sg, "0");
	sg >>= 999u;
	check("0 >>= 999", sg, "0");

	// Post-increment sur 0
	bigint sh(0);
	bigint sh_old = sh++;
	check("0++ retourne", sh_old, "0");
	check("0++ apres", sh, "1");

	// Beaucoup d'increments
	bigint si(0);
	for (int x = 0; x < 1000; ++x)
		++si;
	check("++0 x1000", si, "1000");

	// Comparaison apres operations
	bigint sj(50);
	sj <<= 2u;  // 5000
	sj >>= 1u;  // 500
	check_bool("50<<2>>1 == 500", sj == bigint(500), true);
	check_bool("500 > 499", sj > bigint(499), true);
	check_bool("500 < 501", sj < bigint(501), true);

	// Addition asymetrique (tailles tres differentes)
	bigint sk(1);
	sk <<= 15u;  // "1000000000000000"
	sk += bigint(1);
	check("10^15 + 1", sk, "1000000000000001");

	// Double self-add en chaine
	bigint sl(1);
	for (int x = 0; x < 30; ++x)
		sl += sl;
	check("1 double 30x = 2^30", sl, "1073741824");

	// Gros nombre + gros nombre
	bigint sm(4294967295u);
	sm <<= 5u;  // "429496729500000"
	sm += bigint(4294967295u);
	check("UINT_MAX<<5 + UINT_MAX", sm, "429501024467295");

	// Copy d'un nombre modifie
	bigint sn(42);
	sn <<= 10u;
	bigint so(sn);
	check("copy apres shift", so, "420000000000");
	so >>= 5u;
	check("copy >>= 5", so, "4200000");
	check("original inchange", sn, "420000000000");

	// Comparaison 0 == 0 apres operations
	bigint sp(12345);
	sp >>= 10u;
	check("12345 >>= 10", sp, "0");
	check_bool("result == 0", sp == bigint(0), true);
	check_bool("result == bigint()", sp == bigint(), true);

	// operator+ ne modifie pas les operandes
	bigint sq(100);
	bigint sr(200);
	bigint ss = sq + sr;
	check("100 + 200", ss, "300");
	check("100 inchange", sq, "100");
	check("200 inchange", sr, "200");

	std::cout << "\n=== Shift amount too large ===" << std::endl;

	// Construire un nombre > UINT_MAX
	bigint huge(4294967295u);
	huge += bigint(1);  // 4294967296 > UINT_MAX

	bigint st(42);
	st <<= huge;
	check("lshift too large", st, "42");

	bigint su(123456);
	su >>= huge;
	check("rshift too large", su, "123456");

	// Encore plus gros
	bigint mega(4294967295u);
	mega += bigint(4294967295u);
	mega += bigint(4294967295u);  // ~12.8 milliards

	bigint sv(999);
	sv <<= mega;
	check("lshift mega too large", sv, "999");
	sv >>= mega;
	check("rshift mega too large", sv, "999");

	std::cout << "\n=== Resultat ===" << std::endl;
	std::cout << g_pass << " passed, " << g_fail << " failed" << std::endl;
	return g_fail > 0 ? 1 : 0;
}
