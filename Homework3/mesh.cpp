#include "defs.hpp"

Mesh::Mesh(vector<int>numofextents){
  dim=numofextents.size();
  size=numofextents;
  totalpoints=1;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= numofextents[i];
}

int Mesh::GetDim(){
  return dim;
}

vector <int> Mesh::GetExtents(){
  return size;
}

int Mesh::total_points(){
  return totalpoints;
}
