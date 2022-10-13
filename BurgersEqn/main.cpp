#include "defs.hpp"
#include "DataMesh.cpp"
#include "dU_dt.cpp"

int main() {
  //parameters most likely to be changed by user:
  //---------------------------------------------
  //N = number of points/ansial resolution
  int N = 70;
  //CF is the Courant Factor
  double CF = 0.1;
  //Nsteps = number of time steps into the future
  int Nsteps=2700, Boundary = 2;
  //---------------------------------------------

  //not to be changed!
  double value;
  //value = value to be assigned to the grid
  vector<int> numofextents={N};
  DataMesh<double> U(Boundary,numofextents), dUt(Boundary,numofextents);
  Patch space(numofextents, {0,1},Boundary);
  DataMesh<bool> Bound(Boundary,numofextents);
  vector<DataMesh<bool>> BoundaryFace(0); 
  Bound.SetBMask(Boundary,numofextents);
  double dx=space.coordinate(1)[0]-space.coordinate(0)[0];
  double dt=dx*CF;
  for (int i=0; i<numofextents.size(); i++){
    DataMesh<bool> BoundaryFaceproj(Boundary,numofextents);
    BoundaryFaceproj.SetBoundaryFace(Bound,i);
    BoundaryFace.push_back(BoundaryFaceproj);
  }
  MoveBoundary BM(numofextents,Boundary);
  dtU<double> der(numofextents,Boundary);

  //creating the wave to use as function U
  //--------------------------------------------- 
  for (int i = Boundary; i<N+Boundary; i++){
    value = sin(2*M_PI*space.coordinate(i)[0])+1.0;
    U.set_single_value(i, value);
  }
  //--------------------------------------------- 

  BM.PeriodicBoundaries(Bound, U);
  BM.usePeriodicBoundaryCondtns(U);
  //change length/precision of answers
  cout.precision(10);
  //output data in format easy to plot w/ Mathematica
  for (int k=0; k<=Nsteps; k++) {
    if(k<=Nsteps) {
      cout<<" "<<endl;
      cout << "Which step? Step=" << k << endl;
      cout << "{";
      for (int i=0; i<N;i++)
	cout << "{" << space.coordinate(i)[0] <<", " << U.get_single_value(i) <<"}, ";
      cout << "{" << space.coordinate(N-1)[0] <<", " <<U.get_single_value(N-1) <<"}}" << endl;
    }
    der.RungeKutta3(U, CF, dUt,Bound, BM, BoundaryFace);
    U+=dUt;
    BM.usePeriodicBoundaryCondtns(U);
  }
  //dx is output based on chosen parameters once executable is run
  cout<<"dx is "<<dx<<endl;
  return 0;
}
