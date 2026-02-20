#include "bigint.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a = " << a << std::endl;
    std::cout << "d = " << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;

	std::cout << "=== Test d'overflow avec bigint ===" << std::endl;
	std::cout << "UINT_MAX = " << std::numeric_limits<unsigned int>::max() << std::endl;
	std::cout << std::endl;

	// Test 1: Shift normal (OK)
	bigint z(42);
	bigint shift1(10);
	std::cout << "Test 1 - Shift normal:" << std::endl;
	std::cout << "42 <<= 10 = " << (z <<= shift1) << std::endl;
	std::cout << std::endl;

	// Test 2: Shift avec un nombre proche de UINT_MAX (OK)
	bigint x(100);
	bigint shift2(4294967295u);  // UINT_MAX
	std::cout << "Test 2 - Shift avec UINT_MAX:" << std::endl;
	std::cout << "100 <<= " << shift2 << " = ";
	x <<= shift2;
	std::cout << x.getNbr().substr(0, 50) << "... (" << x.getNbr().size() << " digits)" << std::endl;
	std::cout << std::endl;

	// Test 3: Shift avec overflow (PROBLÈME)
	bigint q(42);
	bigint huge(999999999u);
	huge += bigint(999999999u);
	huge += bigint(999999999u);
	huge += bigint(999999999u);
	huge += bigint(999999999u);  // huge > UINT_MAX
	
	std::cout << "Test 3 - Shift avec overflow:" << std::endl;
	std::cout << "huge = " << huge << " (> UINT_MAX)" << std::endl;
	std::cout << "42 <<= huge = ";
	q <<= huge;
	std::cout << q << std::endl;
	std::cout << std::endl;

	// Test 4: Right shift avec overflow
	bigint o(123456789);
	std::cout << "Test 4 - Right shift avec overflow:" << std::endl;
	std::cout << o << " >>= " << huge << " = ";
	o >>= huge;
	std::cout << o << std::endl;
}