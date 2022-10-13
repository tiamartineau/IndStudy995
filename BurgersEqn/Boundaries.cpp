#include "defs.hpp"
#include "DataMesh.cpp"                                                                                                                                             

//variable 'Boundary' = ghost zone equivalent
MoveBoundary::MoveBoundary(const vector<int> numofextents, const int Boundary){ 
  dim=numofextents.size();
  InternalSize=numofextents;
  totalpoints=1;
  int stepss=1;
  for (int i=0; i<dim;i++){
    totalpoints*=(numofextents[i]+2*Boundary);
    steps.push_back(stepss);
    stepss*=(numofextents[i]+2*Boundary);
  }
}

//Bound = Boundary, just didn't want to call the variable 'B' and forget :-)
void MoveBoundary::PeriodicBoundaries(const DataMesh<bool>& Bound, const DataMesh<double>& mesh_data){ 
  vector <int> coords(dim);
  int l, step;
  double value=0;
  for (int i=0; i<totalpoints; i++){
    if (Bound.get_single_value(i)==1){
      //the fix for if point is outside the bounds of "regular points"/in the ghostzone
      l=i;
      for (int j=1; j<=dim; j++){
	step = l/steps[dim-j];
        coords[j-1]=step;
        l=l%steps[dim-j];
      }
      reverse(coords.begin(),coords.end());
      for (int j=0; j<dim; j++){
	if(coords[j]<Boundaries){
	  grid.push_back({i,i+InternalSize[j]*steps[j]});
	  continue;
	}
	if(coords[j]>=InternalSize[j]+Boundaries){
	  grid.push_back({i,i-InternalSize[j]*steps[j]});
	}
      }
    }
  }
}

//implementing BCs---------------------------------------------------
void MoveBoundary::usePeriodicBoundaryCondtns(DataMesh<double>& mesh_data){
  double value;
  for (int i=0; i<grid.size(); i++){
    value=mesh_data.get_single_value(grid[i][1]);
    mesh_data.set_single_value(grid[i][0],value);
  }
}

void MoveBoundary::usePeriodicBoundaryCondtns(vector<double>& mesh_data){
  double value;
  for (int i=0; i<grid.size(); i++){
    value=mesh_data[grid[i][1]];
    mesh_data[grid[i][0]]=value;
  }
}
