#include "defs.hpp"

template <typename T>
ComputeRHS<T>::ComputeRHS(){}

template <typename T>
void ComputeRHS<T>::FillComputeRHS(const vector <int> numofextents, const int Bounds){
  totalpoints=1;
  int step;
  numofextentss=numofextents;
  Boundss = Bounds;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= (numofextents[i]+2*Bounds);
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    step = 1;
    for (int k=0; k<=i; k++)
      step*=(numofextents[k]+2*Bounds);
    steps.push_back(step);
  }
}

template <typename T>
T ComputeRHS<T>::ThirdDerivative(const vector <T>& H, const int i, const  DataMesh<bool>& B){
  T m2, m1,p1,p2, result;
  result=0;
  if (B.get_single_value(i)==0){ //if the point is not masked 
    m2=H[i-2*steps[0]];
    m1=H[i-steps[0]];
    p2=H[i+2*steps[0]];
    p1=H[i+steps[0]];
    result=-(m2-8.0*m1+8.0*p1-p2)/12;
  }
  return result;
}

template <typename T>
T ComputeRHS<T>::ThirdDerivative(const DataMesh<T>& U, const int i, const DataMesh<bool>& B) {
  T m2, m1,p1,p2, result;
  result=0;
  if(B.get_single_value(i)==0){
    m2=U.get_single_value((i-2*steps[0]+totalpoints)%totalpoints);
    m1=U.get_single_value((i-steps[0]+totalpoints)%totalpoints);
    p1=U.get_single_value((i+steps[0]+totalpoints)%totalpoints);
    p2=U.get_single_value((i+2*steps[0]+totalpoints)%totalpoints);
    result=-(m2-8.0*m1+8.0*p1-p2)/12;
  }
  return result;
}
template <typename T>
T ComputeRHS<T>::burger(const T u)const{
  return -u*u/2;
}

template <typename T>
T ComputeRHS<T>::advectionfl(const T u)const{
  return -u;
}
