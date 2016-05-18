#include "complejo.h"

double Complejo::getR(){
	return rl;
}

double Complejo::getI(){
	return im;
}

Complejo::Complejo(double a,double b){
	rl = a;
	im = b;
}
Complejo::Complejo(){
	rl = 0;
	im = 0;
}

Complejo Complejo::operator+(Complejo z){
	return *new Complejo(rl + z.getR(),im + z.getI());
}
Complejo Complejo::operator-(Complejo z){
	return *new Complejo(rl - z.getR(),im - z.getI());
}
Complejo Complejo::operator*(Complejo z){
	return *new Complejo(rl * z.getR() - im * z.getI(),rl * z.getI() + im * z.getR());
}

Complejo Complejo::operator/(Complejo z){
	if( z.rl == 0 && z.im == 0 ){
		cout << "ERROR: ERROR ENTRE CERO ";
		return z;
	}
	double r1 = sqrt(rl * rl + im * im);
	double r2 = sqrt(z.getR() * z.getR() + z.getI() * z.getI());
	double O1 = atan(im / rl);
	double O2 = atan(z.getI() / z.getR());
	double R = r1 / r2;
	double O = O1 - O2;
	return *new Complejo(R*cos(O), R*sin(O));
}

void Complejo::imprime(){
	cout << rl;
	if (im >= 0) cout << " + " << im;
	else	cout << " - " << -im;
	cout << "i \n";	
}
