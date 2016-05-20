#ifndef COMPLEJO
#define COMPLEJO

#include <iostream>
#include <math.h>
using namespace std;
class Complejo{
	private:
		double real;
		double im;
	public:
		Complejo(double, double);
		Complejo();
		Complejo operator+(Complejo z);
		Complejo operator-(Complejo z);
		Complejo operator*(Complejo z);
		Complejo operator/(Complejo z);
		/* Inicio Practica 4 */
		double magnitud();
		bool mag_eq(Complejo z);
		bool mag_ne(Complejo z);
		bool operator<(Complejo z);
		bool operator<=(Complejo z);
		bool operator>(Complejo z);
		bool operator>=(Complejo z);
		bool operator==(Complejo z);
		bool operator!=(Complejo z);
		bool operator||(Complejo z);
		bool operator&&(Complejo z);
		/* Fin Practica 4 */
		void imprime();
		double getR();
		double getI();
};

#endif
