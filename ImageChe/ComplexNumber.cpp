#include "stdafx.h"
#include "ComplexNumber.h"


ComplexNumber::ComplexNumber()
{
}


ComplexNumber::~ComplexNumber()
{
}
ComplexNumber  ComplexNumber::operator=(ComplexNumber &pt)
{
	this->real= pt.real;
	this->imag= pt.imag;
	return *this;
}

ComplexNumber  ComplexNumber::operator*(ComplexNumber &pt1)
{
ComplexNumber temp;
temp.real = this->real*pt1.real - this->imag*pt1.imag;
temp.imag = this->real*pt1.imag + this->imag*pt1.real;
return temp;
}
/*
ComplexNumber  operator *(ComplexNumber &pt1, ComplexNumber &pt2)
{
ComplexNumber temp;
temp.real = pt2.real*pt1.real - pt2.imag*pt1.imag;
temp.imag = pt2.real*pt1.imag + pt2.imag*pt1.real;
return temp;
}
*/

ComplexNumber  ComplexNumber::operator+(ComplexNumber &pt1)
{
	ComplexNumber temp;
	temp.real = this->real+pt1.real;
	temp.imag = this->imag+pt1.imag;
	return temp;
}
ComplexNumber  ComplexNumber::operator-(ComplexNumber &pt1)
{
	ComplexNumber temp;
	temp.real = this->real - pt1.real;
	temp.imag = this->imag - pt1.imag;
	return temp;
}
ComplexNumber  operator /(ComplexNumber &pt1, double Num)
{
	ComplexNumber temp;
	temp.real = pt1.real/Num;
	temp.real = -pt1.imag / Num;
	return temp;
}
ComplexNumber  operator *(ComplexNumber &pt1, double Num)
{
	ComplexNumber temp;
	temp.real = pt1.real * Num;
	temp.real = pt1.imag * Num;
	return temp;
}
/*
用来求复数的模值
*/
double ComplexNumber::ComplexNumber_sqrt()
{
	double temp;
	temp =sqrt( this->real* this->real+ this->imag* this->imag);
	return temp;
}
