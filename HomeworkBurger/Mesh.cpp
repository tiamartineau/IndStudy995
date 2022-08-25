#include "defs.hpp"

Mesh::Mesh(){}

Mesh::Mesh(const vector<int>numofextents){
  dim=numofextents.size();
  size=numofextents;
  totalpoints=1;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= numofextents[i];
}

Mesh::Mesh(const vector<int> numofextents, const int Bounds){
  dim=numofextents.size();
  totalpoints=1;
  for (int i=0; i<dim; i++){
    totalpoints *=(numofextents[i]+2*Bounds);
    size.push_back(numofextents[i]+2*Bounds);
  }
}

int Mesh::GetDim() const{
  return dim;
}
vector <int> Mesh::Getnumofextents() const{
  return size;
}
int Mesh::GetNpoints() const{
  return totalpoints;
}
