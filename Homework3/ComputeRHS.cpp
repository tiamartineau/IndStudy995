#include "defs.hpp"

template <typename T>
ComputeRHS<T>::ComputeRHS(vector <int> numofextents){
  totalpoints=1;
  int step;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= numofextents[i];
  for (int i=0;i<totalpoints;i++)
    derivative.push_back(0);
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    step = 1;
    for (int k=0; k<=i; k++)
      step*=numofextents[k];
    steps.push_back(step);
  }
}

template <typename T>
void ComputeRHS<T>::UpstreamDifferencing(DataMesh<T>& U, const double dt, DataMesh<T>& dtU){
  T current_point, last_point, result;
  for (int i=0; i<totalpoints; i++){
    current_point=U.get_single_value(i);
    last_point=U.get_single_value((i-steps[0]+totalpoints)%totalpoints);
    result=-dt*(current_point-last_point);
    dtU.set_single_value(i,result);
  }
}

template <typename T>
void ComputeRHS<T>::DownstreamDifferencing(DataMesh<T>& U, const double dt, DataMesh<T>& dtU){
  T current_point, next_point, result;
  for (int i=0; i<totalpoints; i++){
    current_point=U.get_single_value(i);
    next_point=U.get_single_value((i+steps[0]+totalpoints)%totalpoints);
    result=-dt*(next_point-current_point);
    dtU.set_single_value(i,result);
  }
}

template <typename T>
void ComputeRHS<T>::CenteredDifferencing(DataMesh<T>& U, const double dt, DataMesh<T>& dtU){
  T last_point, next_point, result;
  for (int i=0; i<totalpoints; i++){
    last_point=U.get_single_value((i-steps[0]+totalpoints)%totalpoints);
    next_point=U.get_single_value((i+steps[0]+totalpoints)%totalpoints);
    result=-dt*(next_point-last_point)/2;
    dtU.set_single_value(i,result);
  }
}

template <typename T>
void ComputeRHS<T>::RungeKutta3 (DataMesh<T>& U, const double dt, DataMesh<T>& dtU) {

  //values below from table for Kutta's third-order method
  double c1=0, a11=0, a12=0, a13=0;
  double c2=1.0/2.0, a21=1.0/2.0, a22=0, a23=0;
  double c3=1, a31=-1, a32=2, a33=0;
  double b1=1.0/6.0, b2=2.0/3.0, b3=1.0/6.0;

  vector <T> helper(totalpoints), helper1(totalpoints), k1(totalpoints), k2(totalpoints), k3(totalpoints);
  for (int i=0; i<totalpoints;i++){
    k1[i]=ThirdDerivative(U, i);
    helper[i]=U.get_single_value(i) + dt*a21*k1[i];
  }
  for (int i=0; i<totalpoints; i++){
    k2[i]=ThirdDerivative(helper, i);
    helper1[i]=U.get_single_value(i)+dt*(a31*k1[i]+a32*k2[i]);
  }
  for (int i=0; i<totalpoints; i++) {
    k3[i] = ThirdDerivative(helper1, i);
    dtU.set_single_value(i, dt*(b1 * k1[i] + b2 * k2[i] + b3 * k3[i]));
  }
}

template <typename T>
T ComputeRHS<T>::ThirdDerivative(vector <T>& helper, const int i){
  T pointm2, pointm1,pointp1,pointp2, result;
  pointm2=helper[(i-2*steps[0]+totalpoints)%totalpoints];
  pointm1=helper[(i-steps[0]+totalpoints)%totalpoints];
  pointp2=helper[(i+2*steps[0]+totalpoints)%totalpoints];
  pointp1=helper[(i+steps[0]+totalpoints)%totalpoints];
  result=-(pointm2-8.0*pointm1+8.0*pointp1-pointp2)/12;
  return result;
}

template <typename T>
T ComputeRHS<T>::ThirdDerivative(DataMesh<T>& U, const int i) {
  T pointm2, pointm1,pointp1,pointp2, result;
  pointm2=U.get_single_value((i-2*steps[0]+totalpoints)%totalpoints);
  pointm1=U.get_single_value((i-steps[0]+totalpoints)%totalpoints);
  pointp1=U.get_single_value((i+steps[0]+totalpoints)%totalpoints);
  pointp2=U.get_single_value((i+2*steps[0]+totalpoints)%totalpoints);
  result=-(pointm2-8.0*pointm1+8.0*pointp1-pointp2)/12;
  return result;
}

template <typename T>
T ComputeRHS<T>::advection(const T u)const{
  return -u;
}
