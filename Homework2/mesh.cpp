#include <vector>
#include <iostream>

class Mesh{
public:
  Mesh(int dims, std::vector<int> extents);
  int dimensions(void);
  std::vector<int>extents(void);
  int total_points(void);

protected:
  int dims;  // dimensions
  std::vector<int> ext; // points along each axis
  int totalpoints; // total points in mesh
};

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

int main()
{
  std::cout<<"To manipulate size/dimensions of mesh, edit vector 'extents' in main()"<<std::endl;
  std::vector<int> extents = {12,8,9,15};
  Mesh mesh = Mesh(extents.size(),extents);
  {
    std::cout << "There are " << mesh.dimensions() << " spatial dimensions,"<<std::endl;
  std::vector<int> exts = mesh.extents();
  std::cout << "The extents, or grid points along each dimension, are ";
   for (int i=0; i<exts.size();i++){
     std::cout << exts[i] << ", ";
         }
   std::cout << std::endl;
   std::cout << "There are " << mesh.total_points() << " total grid points."<<std::endl;
 }
  
}
