#ifndef COMPLEJO
#define COMPLEJO

#include <bits/stdc++.h>
using namespace std;
class Complejo{
	private:
		double rl;
		double im;
	public:
		Complejo(double,double);
		Complejo();
		Complejo operator+(Complejo z);
		Complejo operator-(Complejo z);
		Complejo operator*(Complejo z);
		Complejo operator/(Complejo z);
		void imprime();
		double getR();
		double getI();
};

#endif