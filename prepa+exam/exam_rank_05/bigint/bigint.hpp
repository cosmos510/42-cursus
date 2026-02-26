#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include<limits>

class bigint {

	private:
		std::string _nbr;
		std::string _numToStr(unsigned int n) const;
		unsigned int _findShiftAmnt(const bigint &b) const;

	public:
		bigint();
		~bigint();
		bigint(unsigned int n);
		bigint(const bigint &c);

		bigint &operator=(const bigint &r);

		bigint operator+(const bigint &r)const;
		bigint operator++(int n);
		bigint &operator++();
		bigint &operator+=(const bigint &r);

		bigint operator<<(unsigned int n)const;
		bigint operator<<(const bigint &r)const;
		bigint &operator<<=(unsigned int n);
		bigint &operator<<=(const bigint &r);

		bigint operator>>(unsigned int n)const;
		bigint operator>>(const bigint &r)const;
		bigint &operator>>=(unsigned int n);
		bigint &operator>>=(const bigint &r);

		bool operator==(const bigint &r) const;
		bool operator!=(const bigint &r) const;
		bool operator>(const bigint &r) const;
		bool operator<(const bigint &r) const;
		bool operator>=(const bigint &r) const;
		bool operator<=(const bigint &r) const;


		std::string getNbr() const;
};

std::ostream &operator<<(std::ostream &o, const bigint &r);