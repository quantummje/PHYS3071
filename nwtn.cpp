#include <iostream>
#include <cmath>

double func(double x) {

	double out;

	//out = cos(4*x) - x;
	out = x*x -5*x - 0.0;

	return out;
}

double deriv(double x) {

	double dx = 0.05;
	double dfdx;

	dfdx = (func(x + dx) - func(x - dx))/(2*dx);

	return dfdx;
}

int main() {

	double ini = 0.0;
	double xn, xi;

	for (int i=0; i<10; i++) {

		if (i==0) {
			xi = ini;
		}
		else {
			xi = xn;
		}

		xn = xi - func(xi)/deriv(xi);

		std::cout << "after " << i << " iterations, xn = " << xn << std::endl;
		std::cout << "after " << i << " iterations, f(xn) = " << func(xn) << std::endl;
		std::cout << "after " << i << " iterations, f'(xn) = " << deriv(xn) << std::endl;
		std::cout << "after " << i << " iterations, delta(xn) = " << -func(xn)/deriv(xn) << std::endl;

	}

	std::cout << "final value of xn = " << xn << " and f(xn) = " << func(xn) << std::endl;
}
