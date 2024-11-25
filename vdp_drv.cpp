#include <iostream>
#include <fstream>
#include <cmath>
#include <tuple>

double deriv_v(double x, double v, double t, double mu) {

  return mu*(1 - pow(x,2))*v - x + 1.2*sin(2*M_PI*t/10.0);
}

double deriv_x(double v) {

  return v;
}

std::tuple<double, double, double, double, double, double, double, double> get_dfs(double x, double v, double t, double mu, double dt) {
  double v0 = 0.0, v1 = 0.0, v2 = 0.0, v3 = 0.0;
  double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0;

  x0 = deriv_x(v);
  v0 = deriv_v(x,v,t,mu);

  x1 = deriv_x(v+0.5*dt*v0);
  v1 = deriv_v(x+0.5*dt*x0,v+0.5*dt*v0,t+0.5*dt,mu);

  x2 = deriv_x(v+0.5*dt*v1);
  v2 = deriv_v(x+0.5*dt*x1,v+0.5*dt*v1,t+0.5*dt,mu);

  x3 = deriv_x(v+dt*v2);
  v3 = deriv_v(x+dt*x2,v+dt*v2,t+dt,mu);

  return std::make_tuple(x0,x1,x2,x3,v0,v1,v2,v3);
}

int main() {
  using namespace std;

  double dt = 0.05, ti = 0.0, tf = 500;
  double xi = 1.0, vi = 0.1;
  double mu = 8.53;
  int Nt = (tf-ti)/dt, smp = 1000;
  double v0 = 0.0, v1 = 0.0, v2 = 0.0, v3 = 0.0;
  double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0;
  double tsc[Nt], v[Nt], x[Nt];

  v[0] = vi;
  x[0] = xi;

  tsc[0] = ti;

  for (int i=0; i<Nt-1; i++) {

    tsc[i+1] = tsc[i] + dt;

    tie(x0,x1,x2,x3,v0,v1,v2,v3) = get_dfs(x[i],v[i],tsc[i],mu,dt);

    x[i+1] = x[i] + (dt/6.0)*(x0 + 2*x1 + 2*x2 + x3);

    v[i+1] = v[i] + (dt/6.0)*(v0 + 2*v1 + 2*v2 + v3);

  }

  std::ofstream datafile;

  datafile.open("vdp_drv_dat.dat");

  if (datafile.is_open()) {

    for (int i=0; i<Nt; i++) {
      if (i % (Nt/smp) == 0) {
        datafile << tsc[i] << "," << x[i] << "," << v[i] << "\n";
      }
    }
  }

  datafile.close();

  return 0;
}
