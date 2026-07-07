#include "test.hpp"

vect2::vect2():_x(0), _y(0){}
vect2::~vect2(){}
vect2::vect2(int x, int y):_x(x), _y(y){}
vect2::vect2(const vect2 &r):_x(r._x), _y(r._y){}

vect2 &vect2::operator=(const vect2 &r){
	_x = r._x;
	_y = r._y;
	return *this;
}

int vect2::operator[](int index)const{
	if (index == 0)
		return _x;
	return _y;
}
int &vect2::operator[](int index){
	if (index == 0)
		return _x;
	return _y;
}

vect2 vect2::operator++(int){
	vect2 tmp(*this);
	++*this;
	return tmp;
}
vect2 vect2::operator--(int){
	vect2 tmp(*this);
	--*this;
	return tmp;
}
vect2 &vect2::operator++(){
	++_x;
	++_y;
	return *this;
}

vect2 &vect2::operator--(){
	--_x;
	--_y;
	return *this;
}

vect2 vect2::operator+(const vect2 &r)const{return vect2(_x+r._x, _y+r._y);}
vect2 vect2::operator+(int n)const{return vect2(_x+n, _y+n);}
vect2 &vect2::operator+=(const vect2 &r){
	_x+=r._x;
	_y+=r._y;
	return *this;
}

vect2 &vect2::operator+=(int n){
	_x+=n;
	_y+=n;
	return *this;
}

vect2 vect2::operator-(const vect2 &r)const{return vect2(_x-r._x, _y-r._y);}
vect2 &vect2::operator-=(const vect2 &r){
	_x-=r._x;
	_y-=r._y;
	return *this;
}
vect2 vect2::operator-(int n)const{return vect2(_x-n, _y-n);}
vect2 &vect2::operator-=(int n){
	_x-=n;
	_y-=n;
	return *this;
}

vect2 vect2::operator*(const vect2 &r)const{return vect2(_x*r._x, _y*r._y);}
vect2 &vect2::operator*=(const vect2 &r){
	_x*=r._x;
	_y*=r._y;
	return *this;
}
vect2 vect2::operator*(int n)const{return vect2(_x*n, _y*n);}
vect2 &vect2::operator*=(int n){
	_x*=n;
	_y*=n;
	return *this;
}

vect2 vect2::operator-()const{return vect2(-_x, -_y);}

bool vect2::operator==(const vect2 &r)const{return (_x==r._x && _y==r._y);}
bool vect2::operator!=(const vect2 &r)const{return !(*this==r);}

std::ostream &operator<<(std::ostream &o, const vect2 &r){
	o<<"{"<<r[0]<<", "<<r[1]<<"}";
	return o;
}
vect2 operator+(int n, const vect2 &r){return r+n;}
vect2 operator-(int n, const vect2 &r){return vect2(n-r[0], n-r[1]);}
vect2 operator*(int n, const vect2 &r){return r*n;}
