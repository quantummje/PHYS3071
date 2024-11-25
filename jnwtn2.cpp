#include <iostream>
#include <iomanip>

double f1(double x1, double x2) {

	double out;

	out = 2*x2 - x1 - 1.0;

	return out;
}

double f2(double x1, double x2) {

	double out;

	out = -x1*x2 - 0.5*x2*x2 + 2;

	return out;
}

double pdiv(double x1, double x2, int n, int s) {

	double dx = 0.05;
	double dfdx = 0.0;

	if (n==1 && s==1) {
		dfdx = (f1(x1+dx,x2)-f1(x1-dx,x2))/(2*dx);
	} if (n==1 && s==2) {
		dfdx = (f1(x1,x2+dx)-f1(x1,x2-dx))/(2*dx);
	} if (n==2 && s==1) {
		dfdx = (f2(x1+dx,x2)-f2(x1-dx,x2))/(2*dx);
	} if (n==2 && s==2) {
		dfdx = (f2(x1,x2+dx)-f2(x1,x2-dx))/(2*dx);
	}

	return dfdx;
}

double jac(double x1, double x2, int n, int s) {

	double det_j = 1.0, j_out = 0.0;

	det_j = pdiv(x1,x2,1,1)*pdiv(x1,x2,2,2) - pdiv(x1,x2,1,2)*pdiv(x1,x2,2,1);

	if (n==1 && s==1) {
		j_out = pdiv(x1,x2,2,2) / det_j;
	} else if (n==1 && s==2) {
		j_out =-pdiv(x1,x2,1,2) / det_j;
	} else if (n==2 && s==1) {
		j_out =-pdiv(x1,x2,2,1) / det_j;
	} else if (n==2 && s==2) {
		j_out = pdiv(x1,x2,1,1) / det_j;
	}

	return j_out;
}

int main() {

	double ini_1 = 5.0, ini_2 = 5.0;
	double xn_1, xn_2, xi_1, xi_2;
	double j11, j12, j21, j22;
	int pnum = 17;

	for (int i=0; i<10; i++) {

		if (i==0) {
			xi_1 = ini_1;
			xi_2 = ini_2;
		} else {
			xi_1 = xn_1;
			xi_2 = xn_2;
		}

		j11 = jac(xi_1,xi_2,1,1);
		j12 = jac(xi_1,xi_2,1,2);
		j21 = jac(xi_1,xi_2,2,1);
		j22 = jac(xi_1,xi_2,2,2);

		xn_1 = xi_1 - j11*f1(xi_1,xi_2) - j12*f2(xi_1,xi_2);
		xn_2 = xi_2 - j21*f1(xi_1,xi_2) - j22*f2(xi_1,xi_2);

		std::cout << "after " << i+1 << " iterations, xn=(" << std::setprecision(pnum) << xn_1 << "," << std::setprecision(pnum) << xn_2 << ")" << std::endl;

	}
	std::cout << "final value of xn=(" << std::setprecision(pnum) << xn_1 << "," << std::setprecision(pnum) << xn_2 << ") and f(x)=(" << std::setprecision(pnum) << f1(xn_1,xn_2) << "," << std::setprecision(pnum) << f2(xn_1,xn_2) << ")" << std::endl;
	std::cout << std::setprecision(pnum) << xn_1 << std::endl;
}
