#include <iostream>
#include <math.h>
using namespace std;
class Complejo {
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
		void imprime();
		double getR();
		double getI();
};

double Complejo::getR() {
	return real;
}

double Complejo::getI() {
	return im;
}

Complejo::Complejo(double a, double b) {
	real = a;
	im = b;
}
Complejo::Complejo() {
	real = 0;
	im = 0;
}

Complejo Complejo::operator+(Complejo z) {
	return *new Complejo(real + z.getR(), im + z.getI());
}

Complejo Complejo::operator-(Complejo z) {
	return *new Complejo(real - z.getR(),im - z.getI());
}

Complejo Complejo::operator*(Complejo z) {
	return *new Complejo(real * z.getR() - im * z.getI(), real * z.getI() + im * z.getR());
}

Complejo Complejo::operator/(Complejo z) {
	/*
	if( z == *(new Complejo(0,0)) ){
		cout << "ERROR: ERROR ENTRE CERO ";
		return z;
	}
	*/
	double r1 = sqrt(real * real + im * im);
	double r2 = sqrt(z.getR() * z.getR() + z.getI() * z.getI());
	double O1 = atan(im / real);
	double O2 = atan(z.getI() / z.getR());
	double R = r1 / r2;
	double O = O1 - O2;
	return *new Complejo(R * cos(O),R * sin(O));
}

void Complejo::imprime(){
	cout << real << " + " << im << "i" << endl;
}
