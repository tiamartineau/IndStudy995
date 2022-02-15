#include<iostream>
#include<cmath>
#include<vector>

//this code is giving me something for coefficients... but I know it is not correct... at all
//assumptions made about using a value for dx may have skewed the answers?
std::vector<double> interp_coeff (int n, double x, const double dx){
  std::vector<double> interpfunc;
  double xi,xj;
  int i, j;
  for(i=0.0;i<n;i++){
    interpfunc.push_back(1.);
      //pushback: Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element. Need to include to avoid seg fault, note to self
      xi = (i-1.0)*dx;
      for(j=0.0;j<n;j++){
	  if (j!=i){
	    xj=(j-1.0)*dx;
	    interpfunc[i] *= (x-xj)/(xi-xj);
	    }
        }
    }
return interpfunc;
}

int main(){
  int i;
  for (i=2.0;i<=6.0;i=i+2.0){
      double x = ((i-1.0)/2.0);
      double dx=0.1;
      std::vector<double> ai = interp_coeff(i,x,dx);

      std::cout<< "While n = " << i << ", the coefficients are: "<<std::endl;
      int j;
      for (j=0.0;j<i;j++){
	  std::cout<< ai[j] << ", "<<std::endl;
	}
    }
  for (i=3.0;i<=7.0;i=i+2.0){
      double x = i/2.0;
      double dx=0.1;
      std::vector<double> ai = interp_coeff(i,x,dx);

      std::cout << "While n = " << i << ", the coefficients are: "<<std::endl;
      int j;
      for (j=0.;j<i;j++){
	  std::cout<< ai[j] << ", "<<std::endl;
	}
    }
}
