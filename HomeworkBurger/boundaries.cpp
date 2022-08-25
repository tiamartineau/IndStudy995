#include "defs.hpp"
#include "DataMesh.cpp"

//definition of 'Bounds', 'MoveBounds' etc. in main.cpp
//essentially, nothing being computed, just copying
//data at overlapping points at the boundaries
//I do not know that this is even necessary for such a small project!!
//but, may as well include them
MoveBounds::MoveBounds(const vector<int> numofextents, const int Bounds){ 
  dim=numofextents.size();
  //internal grid length below
  extents_within=numofextents;
  Npnts=1;
  //I absolutely could have named these better, but, ... it works
  Boundss=Bounds;
  int stepss=1;
  for (int i=0; i<dim;i++){
    Npnts*=(numofextents[i]+2*Bounds);
    steps.push_back(stepss);
    stepss*=(numofextents[i]+2*Bounds);
  }
}

//For creating periodic boundary conditions:
void MoveBounds::GeneratePeriodicB(const DataMesh<bool>& B, const DataMesh<double>& mesh_data){ 
  vector <int> coords(dim);
  int l, step;
  double value=0;
  for (int i=0; i<Npnts; i++){
    //test to see if the points are within the boundaries
    if (B.get_single_value(i)==1){
      l=i;
      //to get the coordinates for each point
      for (int j=1; j<=dim; j++){
	step = l/steps[dim-j];
        coords[j-1]=step;
        l=l%steps[dim-j];
      }
      reverse(coords.begin(),coords.end());
      for (int j=0; j<dim; j++){
	if(coords[j]<Boundss){
	  grid.push_back({i,i+extents_within[j]*steps[j]});
	  continue;
	}
	if(coords[j]>=extents_within[j]+Boundss){
	  grid.push_back({i,i-extents_within[j]*steps[j]});
	}
      }
    }
  }
}

//now implementing those periodic boundary conditions
void MoveBounds::use_boundary_condtns(DataMesh<double>& mesh_data){
  double value;
  for (int i=0; i<grid.size(); i++){
    value=mesh_data.get_single_value(grid[i][1]);
    mesh_data.set_single_value(grid[i][0],value);
  }
}

void MoveBounds::use_boundary_condtns(vector<double>& mesh_data){
  double value;
  for (int i=0; i<grid.size(); i++){
    value=mesh_data[grid[i][1]];
    mesh_data[grid[i][0]]=value;
  }
}
