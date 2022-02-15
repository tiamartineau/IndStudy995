#include<iostream>
#include<cmath>
#include<vector>

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
  double dx, x1, x2, y1, y2, error, y; 
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
  x1 = 2.5*dx;
  x2= 5.5*dx;
  y1 = interpfunc(x1,v,N,dx);
  y2 = interpfunc(x2,v,N,dx);
  delete [] v;
  //Heavisde step function
  v = new double[N];
  for (int i=0; i<N; i++) {
    //again, xi? or x??
    v[i] = heaviside((i-1.0)*dx);
  }
  y1 = interpfunc(x1,v,N,dx);
  y2 = interpfunc(x2,v,N,dx);
  delete [] v;
  //resolution given in email, I believe...
  std::vector<double> res{1,0.5,0.1, 0.05};
  //  double *v;  
  v = new double[N];
  std::cout <<"------------------------"<<std::endl;
  std::cout << "Smooth function" << std::endl;
  std::cout <<"------------------------"<<std::endl;
  for (int j = 0; j<res.size();j++) {
    dx = res[j];
    for (int i = 0; i < N; i++) {
      v[i] = smoothfunction(i * dx);
    }
    y = smoothfunction(x1);
    y1 = interpfunc(x1,v,N,dx);
    error = fabs(y1-y);
    std::cout << "for dx = " << dx << ", error = " << error << std::endl;
  }
  std::cout <<"------------------------"<<std::endl;
  std::cout << "Heaviside step function" << std::endl;
  std::cout <<"------------------------"<<std::endl;
  for (int j = 0; j<res.size();j++) {
    dx = res[j];
    for (int i = 0; i < N; i++) {
      v[i] = heaviside(i * dx);                                                                                                                                                                                                                               
    }
    double y = heaviside(x1);                                         
    y1 = interpfunc(x1,v,N,dx);
    error = fabs(y1-y);
    std::cout << "for dx = " << dx << ", error = " << error << std::endl;
  }
   std::cout << "Copying code from 1 question into another is bad."<<std::endl;
   std::cout << "but this assignment is already late, I hope we can pretend like I did not"<<std::endl;
   std::cout << "You can roast me later." << std::endl;
}
