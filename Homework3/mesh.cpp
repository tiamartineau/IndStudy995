#include <vector>
#include <iostream>
#include "defs.hpp"

Mesh::Mesh(int dimension, std::vector<int> extents){
  dims=dimension;
  ext=extents;
  totalpoints=1;
  for(int i=0;i<dims;i++){
      totalpoints *= ext[i];
    }
}

int Mesh::dimensions(void){
  return dims;
}
std::vector<int> Mesh::extents(void){
  return ext;
}
int Mesh::total_points(void){
  return totalpoints;
}
