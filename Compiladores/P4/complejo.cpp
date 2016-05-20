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
	if (z.real == 0 && z.im == 0) {
		cout << "ERROR: DIVISION ENTRE CERO\n";
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

double Complejo::magnitud() {
	return sqrt(real*real + im*im);
}

bool Complejo::mag_eq(Complejo z) {
	return magnitud() == z.magnitud();
}

bool Complejo::mag_ne(Complejo z) {
	return magnitud() != z.magnitud();
}

bool Complejo::operator<(Complejo z) {
	return (magnitud() < z.magnitud());
}

bool Complejo::operator<=(Complejo z) {
	return (magnitud() <= z.magnitud());
}

bool Complejo::operator>(Complejo z) {
	return (magnitud() > z.magnitud());
}

bool Complejo::operator>=(Complejo z) {
	return (magnitud() >= z.magnitud());
}

bool Complejo::operator==(Complejo z) {
	return (im == z.getI() && real == z.getR());	
}
bool Complejo::operator!=(Complejo z) {
	return (im != z.getI() || real != z.getR());
}

bool Complejo::operator||(Complejo z) {
	return (magnitud() != Complejo().magnitud() || z.magnitud() != Complejo().magnitud());
}

bool Complejo::operator&&(Complejo z) {
	return (magnitud() != Complejo().magnitud() && z.magnitud() != Complejo().magnitud());
}

void Complejo::imprime(){
	cout << real;
	if (im >= 0) cout << " + " << im;
	else	cout << " - " << -im;
	cout << "i \n";	
}
