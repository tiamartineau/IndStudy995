#include "defs.hpp"
#include "datamesh.cpp"
#include "ComputeRHS.cpp"

int main() {
  //N = number of points/spatial resolution
  int N = 100;
  //Nsteps = number of time steps into the future                                                                                                            
  int Nsteps=2;
  //CF is the Courant Factor
  // https://www.simscale.com/blog/2017/08/cfl-condition/
  double CF = 0.1;
  double value;
  //value meaning value to be assigned to the grid
  DataMesh<double> U({N}), dtU({N});
  ComputeRHS<double> der({N});
  for (int i = 0; i < N; i++){
    value=sin(2*PI*double(i)/(N));
    U.set_single_value(i, value);
  }
  //dictates precision of results, can be changed by user
  cout.precision(10);
  for (int j=0; j<=Nsteps; j++) {
    if(j%(Nsteps)==0) {
      cout << "Step=" << j << endl;
      cout << "{";
      for (int i=0; i<N-1;i++)
	cout << U.get_single_value(i) <<", ";
      cout << U.get_single_value(N-1) <<"}" << endl;
    }
    //UN-COMMENT OUT WHICHEVER METHOD IS PREFERRED
    der.UpstreamDifferencing(U, CF, dtU);
    //der.DownstreamDifferencing(U, CF, dtU);
    //der.CenteredDifferencing(U, CF, dtU);
    //der.RungeKutta3(U, CF, dtU);
    U+=dtU;
  }
  return 0;
}
