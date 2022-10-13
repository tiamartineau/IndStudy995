#include "defs.hpp"
#include "ComputeRHS.cpp"

template <typename T>
dtU<T>::dtU (const vector <int> numofextents,const int Boundary){  //Boundary = ghost zone equivalent
  totalpoints=1;
  int step;
  dim=numofextents.size();
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= (numofextents[i]+2*Boundary);
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    step = 1;
    for (int l=0; l<=i; l++)
      step*=(numofextents[l]+2*Boundary);
    steps.push_back(step);
  }  
  RHS.FillInRHS(numofextents, Boundary);
  vector<T> helLR(2*dim,0), hel(dim,0);
  for (int i=0; i<totalpoints; i++){
    FluxLR.push_back(helLR);
    ULR.push_back(helLR);
    Flux.push_back(hel);
  }
}

//below is the actual Runge Kutta scheme and process done out
//-----------------------------------------------------------
template <typename T>
void dtU<T>::RungeKutta3 (const DataMesh<T>& U, const double dt, DataMesh<T>& dUt,const DataMesh<bool>& Bound, MoveBoundary& BM, const vector<DataMesh<bool>>& BoundaryFace) {
  // constants for the Runge Kutta scheme
  //https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods

  int totalpoints = U.get_size();
  double c1=0, a11=0, a12=0, a13=0;
  double c2=1.0/2.0, a21=1.0/2.0, a22=0, a23=0;
  double c3=1, a31=-1, a32=2, a33=0;
  double b1=1.0/6.0, b2=2.0/3.0, b3=1.0/6.0;
  
  vector <T> H(totalpoints), H1(totalpoints), X(totalpoints), Y(totalpoints), Z(totalpoints);// BurgerRHS(totalpoints); <<don't need this
  //above comment will implement burgers equation twice....
  //X, Y, Z, = k1, k2, k3, according to Runge Kutta documentation

  //first three lines of each section take care of boundary points
  //each 'for loop' contains RK3 computation

  FluxLeftRight(BoundaryFace,U);
  RebuildFlux(BoundaryFace);
  dFlux(Bound,X);
  for (int i=0; i<totalpoints;i++){
    H[i]=U.get_single_value(i) + dt*a21*X[i];
  }
  BM.usePeriodicBoundaryCondtns(H);
  FluxLeftRight(BoundaryFace,H);
  RebuildFlux(BoundaryFace);
  dFlux(Bound,X);
  for (int i=0; i<totalpoints; i++){
    H[i]=U.get_single_value(i)+dt*(a31*X[i]+a32*Y[i]);
  }
  BM.usePeriodicBoundaryCondtns(H1);
  FluxLeftRight(BoundaryFace,H1);
  RebuildFlux(BoundaryFace);
  dFlux(Bound,Z);
  BM.usePeriodicBoundaryCondtns(Z);
  for (int i=0; i<totalpoints; i++){
    dUt.set_single_value(i, dt*(b1 * X[i] + b2 * Y[i] + b3 * Z[i]));
  }
}

//all functions used above are defined below:
//-----------------------------------------------------------

template <typename T>
void dtU<T>::FluxLeftRight(const vector<DataMesh<bool>>& BoundaryFace, const DataMesh<T>& U){
  T uLeft, uRight;
  for (int i=0; i<dim; i++){
    for (int j=0; j<totalpoints; j++){
      if (BoundaryFace[i].get_single_value(j)==0){
        uLeft=U.get_single_value(j-steps[i])+0.5;
        uRight=U.get_single_value(j)-0.5;
        ULR[j][2*i]=uLeft;
        ULR[j][2*i+1]=uRight;
        FluxLR[j][2*i]=RHS.burger(uLeft);
        FluxLR[j][2*i+1]=RHS.burger(uRight);
      }
    }
  }
}

template <typename T>
void dtU<T>::FluxLeftRight(const vector<DataMesh<bool>>& BoundaryFace, const vector<T>& U){
  T uLeft, uRight;
  for (int i=0; i<dim; i++){
    for (int j=0; j<totalpoints; j++){
      if (BoundaryFace[i].get_single_value(j)==0){
        uLeft=U[j-steps[i]];
        uRight=U[j];
        ULR[j][2*i]=uLeft;
        ULR[j][2*i+1]=uRight;
        FluxLR[j][2*i]=RHS.burger(uLeft);
        FluxLR[j][2*i+1]=RHS.burger(uRight);
      }
    }
  }
}

//check to make sure signs are all correct

template <typename T>
int dtU<T>::sign(const T a)const {
  if (a>0)
    return 1;
  else
    return -1;
}

template <typename T>
void dtU<T>::RebuildFlux(const vector<DataMesh<bool>>& BoundaryFace){
  T lambda;
  for (int i=0; i<dim; i++){
    for (int j=0; j<totalpoints; j++){
      if (BoundaryFace[i].get_single_value(j)==0){
	lambda=fmax(fabs(ULR[j][2*i]),fabs(ULR[j][2*i+1]));
        Flux[j][i]=(FluxLR[j][2*i]+FluxLR[j][2*i+1])/2-lambda*(ULR[j][2*i]-ULR[j][2*i+1])/2;
      }
    }
  }
}

template <typename T>
void dtU<T>::dFlux(const DataMesh<bool>& Bound,vector<T>&H){
  T ans;
  for (int i=0; i<totalpoints; i++){
    ans=0;
    if (Bound.get_single_value(i)==0){
      for (int j=0; j<dim; j++){
	ans+=Flux[i+steps[j]][j]-Flux[i][j];
      }
      H[i]=ans;
    }
  }
}
