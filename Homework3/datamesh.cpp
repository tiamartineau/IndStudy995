#include "defs.hpp"
#include <assert.h>
//done a little bit more efficiently than in previous assignments...
//kept many of same function and variable names from previous assignments
//DataMesh constructor

template <typename T>
DataMesh<T>::DataMesh(vector <int> numofextents, T f): Mesh(numofextents){
  int totalpoint=total_points();
  for (int i=0; i<totalpoint; i++){
    mesh_data.push_back(f);
  }
}

template <typename T>
DataMesh<T>::DataMesh(vector <int> numofextents): Mesh(numofextents){
  int totalpoint=total_points();
  for (int i=0; i<totalpoint; i++){
    mesh_data.push_back(0);
  }
}

//Deconstructor
template <typename T>
DataMesh<T>::~DataMesh(){}

//check to see if DataMesh and new data are the same size
//overloads + operator
template <typename T>
DataMesh<T> DataMesh<T>::operator +(const DataMesh<T>& a)
{
  vector<int> size=this->GetExtents();
  if (a.mesh_data.size() != this->mesh_data.size()){
    cout << "DataMesh and new data not same size. :-(" << endl;
    exit(1);
  }

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

//check to see if DataMesh and new data are the same size
//overloads *= operator, for multiplying <int/double> types                                     
// by scalar of the same type.
template <typename T>
void DataMesh<T>::operator +=(const DataMesh<T>& b){
  if (b.mesh_data.size() != this->mesh_data.size()){
    cout << "DataMesh and new data not same size. :-(" << endl;
    exit(1);
  }
  if(typeid(T)== typeid(bool)){
    for (int i = 0; i < mesh_data.size(); i++) {
      this->mesh_data[i] = this->mesh_data[i] * b.mesh_data[i];
    }
  }
  else{
    for (int i=0; i<mesh_data.size(); i++){
      this->mesh_data[i]=this->mesh_data[i]+b.mesh_data[i];
    }
  }
}

//same as above, for * operator
template <typename T>
void DataMesh<T>::operator * (const T a){
  for (int i=0; i<mesh_data.size(); i++){
    mesh_data[i]=a*mesh_data[i];
  }
}
//another check
template <typename T>
void DataMesh<T>::set_single_value(const int i, const T value){
  if (i>=mesh_data.size()){
    cout << "Placement of point expands beyond the size of the mesh data. :-(" << mesh_data.size() << endl;
    exit(1);
  } else {
    mesh_data[i]=value;
  }
}

template <typename T>
T DataMesh<T>::get_single_value (const int i){
  return mesh_data[i];
}

template <typename T>
void DataMesh<T>::Print(){
  for (int i=0; i<mesh_data.size(); i++){
    cout << "i=" << i << ", value=" << mesh_data[i] << endl;
  }
}
