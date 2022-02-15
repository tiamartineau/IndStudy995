#include<iostream>
#include<cmath>
#include<vector>

//I realize the interpfunc could probably just be imported into all of these questions, though I did change it a tiny bit for question 4...

double smoothfunction(const double x) {
  double f;
  f = (x*x-1.0)/(x+2.0);
  return f;
}

double heaviside(const double x) {
  double f=0.0;
  if (x>0.15)
    f=1.0;
  return f;
}

double interpfunc(const double x, const double* v, const int N, const double dx) {
  double term, xi, xj;
  double result = 0;
  int i, j;
  for (i=0.0; i<N; i++) {
    term = 1.0;
    //defined:
    xi = (i-1.0)*dx;
    for (j=0; j<N; j++) {
      if (j!=i) {
        xj=(j-1.0)*dx;
        term = term*(x-xj)/(xi-xj);
      }
    }
    term = term*v[i];
    result = result+term;
  }
  return result;
}

int main()
{
  int N;
  double dx, x1, x2, y1, y2;
  double *v;
  N=5.;
  dx=0.1;
  //smooth function
  v = new double[N];
  //v is an empty vector of length N
  for (int i=0; i<N; i++) {
    //is this xi or x below????
    v[i] = smoothfunction((i-1.0)* dx);
  }
  //two cases
  x1 = 2.5*dx;
  x2= 5.5*dx;
  y1 = interpfunc(x1,v,N,dx);
  y2 = interpfunc(x2,v,N,dx);
  std::cout <<"--------------"<<std::endl;
  std::cout <<"Smooth function:"<<std::endl;
  std::cout <<"--------------"<<std::endl;
  std::cout <<"Interpolated values:" <<std::endl;
  std::cout <<"for x=2.5*dx:"<< y1 <<std::endl;
  std::cout <<"and 5.5*dx:" << y2 << std::endl;
  std::cout <<"--------------"<<std::endl;
  std::cout <<"Real values:"<<std::endl;
  std::cout <<"for x=2.5*dx: y=-0.41666"<<std::endl;
  std::cout <<"for x=5.5*dx: y=-0.273529"<<std::endl;
  delete [] v;
  //Heavisde step function
  v = new double[N];
  for (int i=0; i<N; i++) {
    //again, xi? or x??
    v[i] = heaviside((i-1.0)*dx);
  }
  y1 = interpfunc(x1,v,N,dx);
  y2 = interpfunc(x2,v,N,dx);
  std::cout <<"~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout <<"Heaviside step function:" <<std::endl;
  std::cout <<"--------------"<<std::endl;
  std::cout <<"Interpolated values:" <<std::endl;
  std::cout <<"for x=2.5*dx: "<< y1 << std::endl;
  std::cout <<"for x=5.5*dx " << y2 << std::endl;
  std::cout <<"--------------"<<std::endl;
  std::cout <<"Real values:"<<std::endl;
  std::cout <<"for x=2.5*dx: y=1"<<std::endl;
  std::cout <<"for x=5.5*dx: y=1"<<std::endl;
}
