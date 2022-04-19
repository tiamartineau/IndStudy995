#include "defs.hpp"
#include <assert.h>

//Boolean addition operator = AND
//Overloading += for DataMesh<int/double/bool> 
template<typename T>
inline void DataMesh<T>::operator +=(DataMesh<T> overload){
  assert(mesh_data.size() == overload.get_all_points());
  assert(typeid(mesh_data[0]) == typeid(overload.get_single_value(0)));
  if(typeid(T)==typeid(bool)){
    for(int i=0;i<mesh_data.size();i++){
      mesh_data[i] = mesh_data[i]*overload.get_single_value(i);
    }
  }
  else{
    for(int i=0;i<mesh_data.size();i++){
      mesh_data[i] = (T)(mesh_data[i]+overload.get_single_value(i));
    }
  }
}

//Overloading + for datameshes of types <int/double>
//adds entries at corresponding points
template<typename T>
DataMesh<T> DataMesh<T>::operator +(DataMesh<T> overload){
  assert(mesh_data.size() == overload.get_all_points());                 
  assert(overload.dimensions() == dims);
  for(int i=0;i<overload.dimensions();i++){
    assert(overload.extents()[i] == ext[i]);
  }

  DataMesh<T> datamesh = DataMesh(overload.dimensions(), overload.extents());
  T val;
  if(typeid(T)==typeid(bool)){
    for(int i=0;i<overload.get_all_points();i++){
      val = mesh_data[i]*overload.get_single_value(i);
      datamesh.set_single_value(i,val);
    }
  }
  else{
    for(int i=0;i<overload.get_all_points();i++){
      val = (T)(mesh_data[i]+overload.get_single_value(i));
      datamesh.set_single_value(i,val);
    }
  }
  return datamesh;
}

// "" *= operator, for multiplying <int/double> types
// by scalar of the same type.

template<typename T>
void DataMesh<T>::operator *= (T overload_x){
  assert(typeid(overload_x) != typeid(bool));
  for(int i=0;i<mesh_data.size();i++)
    {
      mesh_data[i] *= overload_x;
    }
}
