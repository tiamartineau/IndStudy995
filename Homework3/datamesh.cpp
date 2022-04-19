#include "defs.hpp"
#include <assert.h>

template<typename T>  
DataMesh<T>::DataMesh(int dimensions, std::vector<int> extents)
:Mesh(dimensions,extents)
{
  int product = 1;
  for(int i=0;i<extents.size();i++){
      product *= extents[i];
    }
  mesh_data.resize(product);
}

//comments/definitions provided in defs_hpp if names are not self-explanatory enough!
template<typename T>  
int DataMesh<T>::get_all_points(void){
  return mesh_data.size();
}

template<typename T>  
void DataMesh<T>::set_values(std::vector<T> fill_data){
  if (fill_data.size() != mesh_data.size()){
    std::cout << "DataMesh and new data not same size" << std::endl;
    }
  else{
      for(int i=0;i<mesh_data.size();i++){
	  mesh_data[i] = fill_data[i];
	}
    }
}

template<typename T>  
std::vector<T> DataMesh<T>::retrieve_values(void){
  return mesh_data;
}

template<typename T>  
void DataMesh<T>::set_single_value(int coordinate, T data_point){
  mesh_data[coordinate]=data_point;
}

template<typename T>  
T DataMesh<T>::get_single_value(int coordinate){
  return mesh_data[coordinate];
}

template<typename T>  
void DataMesh<T>::print_datamesh(void){
  int coord;
  for(int i=0;i<ext[0];i++){
      for(int j=0;j<ext[1];j++){
	  for(int k=0;k<ext[2];k++){
	      coord = k*(ext[0]*ext[1])+j*ext[0]+i;
	      std::cout << mesh_data[coord] << " ";
	    }
	  std::cout << std::endl;
	}
      std::cout << std::endl;
    }
}

template class DataMesh<int>;
template class DataMesh<double>;
