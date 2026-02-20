#include "bigint.hpp"

bigint::bigint(): _nbr("0") {}

bigint::bigint(const unsigned int n): _nbr(_numToStr(n)) {}

bigint::bigint(const bigint &cpy): _nbr(cpy._nbr) {}

bigint::~bigint() {}

bigint &bigint::operator=(const bigint &rhs) {
	_nbr = rhs._nbr;
	return *this;
}

bigint &bigint::operator+=(const bigint &rhs) {
	std::string res;
	int carry = 0;
	for (int i = _nbr.size() - 1, j = rhs._nbr.size() - 1; i >= 0 || j >= 0 || carry; --i, --j) {
		int a = i >= 0 ? _nbr[i] - '0' : 0;
		int b = j >= 0 ? rhs._nbr[j] - '0' : 0;
		int sum = a + b + carry;
		carry = sum / 10;
		res = char(sum % 10 + '0') + res;
	}
	_nbr = res;
	return *this;
}

bigint bigint::operator+(const bigint &rhs) const {
	bigint tmp(*this);
	tmp += rhs;
	return tmp;
}

bigint &bigint::operator++() {
	*this += bigint(1);
	return *this;
}

bigint bigint::operator++(int) {
	bigint tmp(*this);
	++(*this);
	return tmp;
}

bigint &bigint::operator<<=(const unsigned int n) {
	if (_nbr != "0")
		_nbr.append(n, '0');
	return *this;
}

bigint &bigint::operator>>=(const unsigned int n) {
	_nbr = n >= _nbr.size() ? "0" : _nbr.substr(0, _nbr.size() - n);
	return *this;
}

bigint bigint::operator<<(const unsigned int n) const {
	bigint tmp(*this);
	tmp <<= n;
	return tmp;
}

bigint bigint::operator>>(const unsigned int n) const {
	bigint tmp(*this);
	tmp >>= n;
	return tmp;
}

bigint &bigint::operator<<=(const bigint &rhs) {
	unsigned int shiftAmnt = _findShiftAmnt(rhs);
	if (_nbr == "0" || shiftAmnt == 0)
		return *this;
	return *this <<= shiftAmnt;
}

bigint &bigint::operator>>=(const bigint &rhs) {
	unsigned int shiftAmnt = _findShiftAmnt(rhs);
	if (_nbr == "0" || shiftAmnt == 0)
		return *this;
	return *this >>= shiftAmnt;
}

bigint bigint::operator<<(const bigint &rhs) const {
	bigint tmp(*this);
	tmp <<= rhs;
	return tmp;
}

bigint bigint::operator>>(const bigint &rhs) const {
	bigint tmp(*this);
	tmp >>= rhs;
	return tmp;
}

bool bigint::operator<(const bigint &rhs) const {
	if (_nbr.size() != rhs._nbr.size())
		return _nbr.size() < rhs._nbr.size();
	return _nbr < rhs._nbr;
}

bool bigint::operator>(const bigint &rhs) const { return rhs < *this; }

bool bigint::operator==(const bigint &rhs) const { return _nbr == rhs._nbr; }

bool bigint::operator!=(const bigint &rhs) const { return !(*this == rhs); }

bool bigint::operator<=(const bigint &rhs) const { return !(*this > rhs); }

bool bigint::operator>=(const bigint &rhs) const { return !(*this < rhs); }

std::string bigint::_numToStr(const unsigned int n) const {
	std::stringstream ss;
	ss << n;
	return ss.str();
}

unsigned int bigint::_findShiftAmnt(const bigint &rhs) const {
	long long shiftAmnt = 0;
	for (size_t i = 0; i < rhs._nbr.size(); ++i)
		shiftAmnt = shiftAmnt * 10 + (rhs._nbr[i] - '0');
	if (shiftAmnt > std::numeric_limits<unsigned int>::max()) {
		std::cerr << "Shift amount too large" << std::endl;
		return 0;
	}
	return static_cast<unsigned int>(shiftAmnt);
}

std::string bigint::getNbr() const { return _nbr; }

std::ostream &operator<<(std::ostream &o, const bigint &rhs) {
	o << rhs.getNbr();
	return o;
}
