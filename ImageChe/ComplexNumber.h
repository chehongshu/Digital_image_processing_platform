#pragma once

class ComplexNumber
{
	public:
	~ComplexNumber();
	ComplexNumber();
	public :
	double imag=0;
	double real = 0;
	 ComplexNumber operator=(ComplexNumber &);//赋值重载
	 ComplexNumber operator*(ComplexNumber &);//乘法重载
	 ComplexNumber operator+(ComplexNumber &);//加法重载
	 ComplexNumber operator-(ComplexNumber &);//减法重载
	 ///ComplexNumber &operator/(ComplexNumber &);//除法重载 类成员重载
	//friend ComplexNumber  operator *(ComplexNumber &, ComplexNumber &);//非类成员重载
	 friend ComplexNumber  operator /(ComplexNumber &pt1, double Num);
	 friend ComplexNumber  operator *(ComplexNumber &pt1, double Num);

	 double ComplexNumber_sqrt();
};

