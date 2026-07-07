#pragma once
#include <iostream>

class vect2{
	private:
		int _x;
		int _y;
	public:
		vect2();
		~vect2();
		vect2(int x, int y);
		vect2(const vect2 &r);

        int operator[](int index)const;
		int &operator[](int index);

		vect2 &operator=(const vect2 &r);

		vect2 operator++(int);
        vect2 operator--(int);
		vect2 &operator++();
		vect2 &operator--();

		vect2 operator+(const vect2 &r)const;
        vect2 operator+(int n)const;
        vect2 &operator+=(int n);
		vect2 &operator+=(const vect2 &r);
		
		
		vect2 operator-(const vect2 &r)const;
        vect2 operator-(int n)const;
		vect2 &operator-=(const vect2 &r);
		vect2 &operator-=(int n);

		vect2 operator*(const vect2 &r)const;
		vect2 &operator*=(const vect2 &r);
        vect2 operator*(int n)const;
		vect2 &operator*=(int n);

		vect2 operator-()const;

		bool operator==(const vect2 &r)const;
		bool operator!=(const vect2 &r)const;
};

std::ostream &operator<<(std::ostream &o, const vect2 &r);
vect2 operator+(int n, const vect2 &r);
vect2 operator-(int n, const vect2 &r);
vect2 operator*(int n, const vect2 &r);