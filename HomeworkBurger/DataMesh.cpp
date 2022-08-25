#include "defs.hpp"

template<typename T>
DataMesh<T>::DataMesh(){}

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
DataMesh<T>::DataMesh(const int Bounds, const vector <int> numofextents): Mesh(numofextents, Bounds){
  int point=GetNpoints();
  for (int i=0; i<point; i++){
    mesh_data.push_back(0);
  }
  int step=1;
  for (int i=0; i<numofextents.size(); i++){
    steps.push_back(step);
    step*=(numofextents[i]+2*Bounds);
  }
}

template <typename T>
void DataMesh<T>::SetBMask(const int Bounds, const vector <int> numofextents){ // the function is used to set B mask
  int point=GetNpoints();
  int l, position;
  vector <int> backwards;
  for (int i=0; i<point; i++){
    l=i;
    for (int j=1; j<=numofextents.size();j++){
      position = l/steps[numofextents.size()-j];
      if (position < Bounds || position >= (numofextents[numofextents.size()-j]+Bounds))
        mesh_data[i]=1;
      l=l%steps[numofextents.size()-j];
    }
  }
}

template <typename T>
void DataMesh<T>::SetBoundaryFace(const DataMesh<T>& B, const  int i){
  int point=GetNpoints();
  bool periodic;
  for (int j=0; j<point; j++){
    periodic=1;
    if (B.get_single_value(j)==0){
      periodic=0;
    }
    if(j>=steps[i]){
      if(B.get_single_value(j-steps[i])==0){
	periodic=0;
      }
    }
    mesh_data[j]=periodic;
  }
}

template<typename T>
DataMesh<T>::~DataMesh(){}

template<typename T>
DataMesh<T> DataMesh<T>::operator+(const DataMesh<T>& a)
{
  vector<int> size=this->Getnumofextents();
  //check to see if DataMesh and new data are the same size
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

template<typename T>
void DataMesh<T>::set_single_value(const int i, const T& a){
  mesh_data[i]=a;
}

//check to see if DataMesh and new data are the same size
template <typename T>
void DataMesh<T>::operator += (const DataMesh<T>& b){
  if (b.mesh_data.size() != this->mesh_data.size()){
    cout << "DataMesh and new data not same size. :-(" << endl;
    exit(1);
  }
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
void DataMesh<T>::Print() const{
  for (int i=0; i<mesh_data.size(); i++){
    cout << "i =" << i << ", it is " << mesh_data[i] << endl;
  }
}
