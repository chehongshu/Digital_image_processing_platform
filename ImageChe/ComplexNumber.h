#pragma once

class ComplexNumber
{
	public:
	~ComplexNumber();
	ComplexNumber();
	public :
	double imag=0;
	double real = 0;
	 ComplexNumber operator=(ComplexNumber &);//��ֵ����
	 ComplexNumber operator*(ComplexNumber &);//�˷�����
	 ComplexNumber operator+(ComplexNumber &);//�ӷ�����
	 ComplexNumber operator-(ComplexNumber &);//��������
	 ///ComplexNumber &operator/(ComplexNumber &);//�������� ���Ա����
	//friend ComplexNumber  operator *(ComplexNumber &, ComplexNumber &);//�����Ա����
	 friend ComplexNumber  operator /(ComplexNumber &pt1, double Num);
	 friend ComplexNumber  operator *(ComplexNumber &pt1, double Num);

	 double ComplexNumber_sqrt();
};

