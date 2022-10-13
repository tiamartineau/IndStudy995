#include "defs.hpp"

//mostly copied from HW3 :-)

Mesh::Mesh(){}

Mesh::Mesh(const vector<int> numofextents){
  dim=numofextents.size();
  size=numofextents;
  totalpoints=1;
  for (int i=0; i<numofextents.size();i++)
    totalpoints *= numofextents[i];
}

//including bounds:

Mesh::Mesh(const vector<int> numofextents, const int Boundary){
  dim=numofextents.size();
  totalpoints=1;
  for (int i=0; i<dim; i++){
    totalpoints *=(numofextents[i]+2*Boundary);
    size.push_back(numofextents[i]+2*Boundary);
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
