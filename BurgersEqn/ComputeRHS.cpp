#include "defs.hpp"
//#include "DataMesh.cpp"

template <typename T>
ComputeRHS<T>::ComputeRHS(){}

template <typename T>
void ComputeRHS<T>::FillInRHS(const vector <int> numofextents, const int Boundary){
  totalpoints=1;
  int step;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= (numofextents[i]+2*Boundary);
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    step = 1;
    for (int k=0; k<=i; k++)
      step*=(numofextents[k]+2*Boundary);
    steps.push_back(step);
  }
}
//value of "U" for Burger's equation
template <typename T>
T ComputeRHS<T>::burger(const T u)const{
  return -u*u/2;
}

template <typename T>
T ComputeRHS<T>::Flux(const vector <T>& H, const int i, const  DataMesh<bool>& Bound){
  T m2, m1,p0,p1,p2,cp, cm, Fp12, Fm12, dx, result;
  result=0;
  if (Bound.get_single_value(i)==0){
    //position -1
    m1=H[i-steps[0]];
    //position 0
    p0=H[i];
    //position +1
    p1=H[i+steps[0]];
    //constants given in formulae for F_{+12}, F_{-12} 
    cp=max(abs(p1),abs(p0));
    cm=max(abs(p0),abs(m1));
    //dx calculated and printed in main.cpp
    dx = 0.01449275362;
    //F_{+12}, F_{-12} 
    Fp12=((burger(p1)+burger(p0))/2)+((cp*(p1-p0))/2);
    Fm12=((burger(p0)+burger(m1))/2)+((cm*(m1-p0))/2);
    //complete RHS:
    result=(Fp12-Fm12)/dx;
  }
  return result;
}

template <typename T>
T ComputeRHS<T>::Flux(const DataMesh<T>& U, const int i,const DataMesh<bool>& Bound){
  T m2, m1,p1,p0,p2,cp,cm, Fp12, Fm12,dx,result;
  result=0;
  int N = U.get_size();
  if(Bound.get_single_value(i)==0){
    //position -1 
    m1=U.get_single_value((i+N-steps[0])%N);
    //position 0
    p0=U.get_single_value(i);
    //position plus 1
    p1=U.get_single_value((i+steps[0]+N)%N);
    //constants given in formulae for F_{+12}, F_{-12}
    cp=max(abs(p1),abs(p0));
    cm=max(abs(m1),abs(p0));
    //dx calculated in main.cpp
    dx = 0.01449275362;
    //F_{+12}, F_{-12}
    Fp12=((burger(p1)+burger(p0))/2)+((cp*(p1-p0))/2);
    Fm12=((burger(p0)+burger(m1))/2)+((cm*(p0-m1))/2);
    //complete RHS:
    result=(Fp12-Fm12)/dx;
  }
  return result;

}
