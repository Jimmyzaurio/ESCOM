#include "complejo.h"

double Complejo::getR(){
	return real;
}

double Complejo::getI(){
	return im;
}

Complejo::Complejo(double a,double b){
	real = a;
	im = b;
}
Complejo::Complejo(){
	real = 0;
	im = 0;
}

Complejo Complejo::operator+(Complejo z){
	return *new Complejo(real + z.getR(),im + z.getI());
}
Complejo Complejo::operator-(Complejo z){
	return *new Complejo(real - z.getR(),im - z.getI());
}
Complejo Complejo::operator*(Complejo z){
	return *new Complejo(real * z.getR() - im * z.getI(),real * z.getI() + im * z.getR());
}

Complejo Complejo::operator/(Complejo z){
	if( z.real == 0 && z.im == 0 ){
		cout << "ERROR: ERROR ENTRE CERO ";
		return z;
	}
	double r1 = sqrt(real * real + im * im);
	double r2 = sqrt(z.getR() * z.getR() + z.getI() * z.getI());
	double O1 = atan(im / real);
	double O2 = atan(z.getI() / z.getR());
	double R = r1 / r2;
	double O = O1 - O2;
	return *new Complejo(R*cos(O), R*sin(O));
}

void Complejo::imprime(){
	cout << real;
	if (im >= 0) cout << " + " << im;
	else	cout << " - " << -im;
	cout << "i \n";	
}
