#include "defs.hpp"
#include "datamesh.cpp"
#include "algebra.cpp"
int main()
{
  //Mesh:
  std::cout<<"To manipulate size/dimensions of mesh, edit vector 'extents' in main()"<<std::\
    endl;
  std::vector<int> extents = {1,3,5,2};
  Mesh mesh = Mesh(extents.size(),extents);{
    std::cout << "There are " << mesh.dimensions() << " spatial dimensions,"<<std::endl;
    std::vector<int> exts = mesh.extents();
    std::cout << "The extents, or grid points along each dimension, are ";
    for (int i=0; i<exts.size();i++){
      std::cout << exts[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "There are " << mesh.total_points() << " total grid points."<<std::endl;
  }

  //boolean data type: true = 1, false = 0

  //DataMeshAlgebra
  DataMesh<int> A = DataMesh<int>(extents.size(),extents);
  DataMesh<int> B = DataMesh<int>(extents.size(),extents);
  DataMesh<bool> Boolcase1 = DataMesh<bool>(extents.size(),extents);
  DataMesh<bool> Boolcase2 = DataMesh<bool>(extents.size(),extents);
  std::cout << "DataMesh created" << std::endl;
  int coord;
  for(int i=0;i<extents[0];i++){
      for(int j=0;j<extents[1];j++){
	  for(int k=0;k<extents[2];k++){
	      coord = k*(extents[0]*extents[1])+j*extents[0]+i;
	      A.set_single_value(coord,i+j+k);
	      B.set_single_value(coord,j);
	      Boolcase1.set_single_value(coord,(bool) (k%2));
	      Boolcase2.set_single_value(coord,(bool) (j%2));
	    }
	}
    }
  std::cout << "DataMesh A:" << std::endl;
  A.print_datamesh();
  std::cout << "DataMesh B:" << std::endl;
  B.print_datamesh();
  A += B;
  std::cout << "Adding the two: A + B:" << std::endl;
  A.print_datamesh();
  std::cout << "DataMesh C: (A + B) + B" << std::endl;
  DataMesh<int> C = A + B;
  C.print_datamesh();
  std::cout << "2 * DataMesh C:" << std::endl;
  C *= 2;
  C.print_datamesh();

  std::cout << "Testing boolean cases, Boolcase1:" << std::endl;
  Boolcase1.print_datamesh();
  std::cout << "Boolcase2:" << std::endl;
  Boolcase2.print_datamesh();
  Boolcase1 = Boolcase1 + Boolcase2;
  std::cout << "Boolcase1 += Boolcase2:" << std::endl;
  std::cout << "(Only true + true will remain true)" << std::endl;
  Boolcase1.print_datamesh();
}
