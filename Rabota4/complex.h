#pragma once
#include <iostream>

struct Complex {

private:
	float re;
	float im;

public: 
	Complex(float r, float i) : re(r), im(i) {}

	Complex() {
		re = 0;
		im = 0;
	}
	
	Complex(int num) {
		re = (float)num;
		im = 0;
	}

	Complex(float num) {
		re = num;
		im = 0;
	}

	friend const Complex operator+ (const Complex& a, const Complex& b) {
		return Complex(a.re + b.re, a.im + b.im);
	}

	friend const Complex operator- (const Complex& a, const Complex& b) {
		return Complex(a.re - b.re, a.im - b.im);
	}

	friend const Complex operator* (const Complex& a, const Complex& b) {
		return Complex(a.re * b.re - a.im * b.im, a.im * b.re + a.re * b.im);
	}

	friend std::ostream& operator<< (std::ostream& out, const Complex& num)
	{
		out << "(" << num.re << ", " << num.im << ')';
		return out;
	}

	friend std::istream& operator>> (std::istream& in, Complex& num)
	{
		in >> num.re;
		in >> num.im;
		return in;
	}

};