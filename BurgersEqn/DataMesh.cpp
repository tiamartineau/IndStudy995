#include "defs.hpp"

template<typename T>
DataMesh<T>::DataMesh(){}

//get_single_value, set_single_value, operators, etc. all seen in previous HW assignments   

template<typename T>
DataMesh<T>::DataMesh(const vector <int> numofextents,const T f): Mesh(numofextents){
  int point=GetNpoints();
  for (int i=0; i<point; i++){
    mesh_data.push_back(f);
  }
  int step=1;
  for (int i=0; i<numofextents.size(); i++){
    steps.push_back(step);
    step*=numofextents[i];
  }
}

template<typename T>
DataMesh<T>::DataMesh(const vector <int> numofextents): Mesh(numofextents){
  int point=GetNpoints();
  for (int i=0; i<point; i++){
    mesh_data.push_back(0);
  }
  int step=1;
  for (int i=0; i<numofextents.size(); i++){
    steps.push_back(step);
    step*=(numofextents[i]);
  }
}

template<typename T>
DataMesh<T>::DataMesh(const int Boundary, const vector <int> numofextents): Mesh(numofextents, Boundary){
  int point=GetNpoints();
  for (int i=0; i<point; i++){
    mesh_data.push_back(0);
  }
  int step=1;
  for (int i=0; i<numofextents.size(); i++){
    steps.push_back(step);
    step*=(numofextents[i]+2*Boundary);
  }
}

template <typename T>
void DataMesh<T>::SetBMask(const int Boundary, const vector <int> numofextents){ 
  //used to set boundary mask
  int point=GetNpoints();
  int l, position;
  vector <int> backwards;
  for (int i=0; i<point; i++){
    l=i;
    for (int j=1; j<=numofextents.size();j++){
      position = l/steps[numofextents.size()-j];
      if (position < Boundary || position >= (numofextents[numofextents.size()-j]+Boundary))
        mesh_data[i]=1;
      l=l%steps[numofextents.size()-j];
    }
  }
}

template <typename T>
void DataMesh<T>::SetBoundaryFace(const DataMesh<T>& Bound, const  int i){ 
//indices here indicate direction, i.e., 0=x, etc.
  int point=GetNpoints();
  bool flag;
  for (int j=0; j<point; j++){
    flag=1;
    if (Bound.get_single_value(j)==0){
      flag=0;
    }
    if(j>=steps[i]){
      if(Bound.get_single_value(j-steps[i])==0){
	flag=0;
      }
    }
    mesh_data[j]=flag;
  }
}

template<typename T>
DataMesh<T>::~DataMesh(){}

template<typename T>
DataMesh<T> DataMesh<T>::operator+(const DataMesh<T>& a)
{
  vector<int> size=this->Getnumofextents();

  DataMesh<T> c(size);
  if(typeid(T)== typeid(bool)) {
    for (int i = 0; i < a.mesh_data.size(); i++) {
      c.mesh_data[i] = a.mesh_data[i]*this->mesh_data[i];
    }
  }
  else{
    for (int i = 0; i < a.mesh_data.size(); i++) {
      c.mesh_data[i] = a.mesh_data[i] + this->mesh_data[i];
    }
  }
  return c;
}

template<typename T>
void DataMesh<T>::set_single_value(const int i, const T& a){
  mesh_data[i]=a;
}

template<typename T>
void DataMesh<T>::Print(){
  cout<<"{";
  for (int i=0; i<mesh_data.size();i++){
    cout<<mesh_data[i]<<",";
  }
  cout<<"}"<<endl;
}

template <typename T>
void DataMesh<T>::operator += (const DataMesh<T>& b){
  if(typeid(T)== typeid(bool)){
    for (int i = 0; i < mesh_data.size(); i++) {
      mesh_data[i] = mesh_data[i] * b.mesh_data[i];
    }
  }
  else{
    for (int i=0; i<mesh_data.size(); i++){
      mesh_data[i]=mesh_data[i]+b.mesh_data[i];
    }
  }
}

template <typename T>
void DataMesh<T>::operator * (const T a){
  for (int i=0; i<mesh_data.size(); i++){
    mesh_data[i]=a*mesh_data[i];
  }
}

template <typename T>
T DataMesh<T>::get_single_value (const int i) const{
  return mesh_data[i];
}

template <typename T>
int DataMesh<T>::get_size () const{
  return mesh_data.size();
}
