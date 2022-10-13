#include "defs.hpp"
#include "DataMesh.cpp"

//lowercase 'bounds' here = length of line of gridpoints in each dim
Patch::Patch(const vector <int> numofextents, const vector <double> bounds): Mesh(numofextents){
  int step;
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    spacing.push_back((bounds[i*2+1]-bounds[i*2])/(numofextents[i]-1));
    step = 1;
    for (int w=0; w<=i; w++)
      step*=numofextents[w];
    steps.push_back(step);
  }
  int totalpoints=GetNpoints();
  for (int i=0; i<totalpoints; i++){
    produce_coords(i);
  }
}

//same Patch, now with periodic boundary information
Patch::Patch(const vector <int> numofextents, const vector <double> bounds, const int Boundary): Mesh(numofextents, Boundary){
  int step;
  steps.push_back(1);
  for (int i =0; i<numofextents.size(); i++){
    spacing.push_back((bounds[i*2+1]-bounds[i*2])/(numofextents[i]-1));
    step = 1;
    for (int k=0; k<=i; k++)
      step*=(numofextents[k]+2*Boundary);
    steps.push_back(step);
  }
  int totalpoints=GetNpoints();
  for (int i=0; i<totalpoints; i++){
    produce_coords(i, Boundary);
  }
}
//--------------------------------------------
//lowercase 'bounds' here = length of line of gridpoints in each dim  
//--------------------------------------------
vector<double> Patch::get_bounds() const{
  return bounds;
}
vector<int> Patch::num_of_steps() const{
  return steps;
}
//--------------------------------------------

void Patch::produce_coords(const int i){
  int l=i, step,length;
  double current_var;
  vector <double> backwards;
  vector<int> sizes = Getnumofextents();
  length=sizes.size();
  for (int j=1; j<=length;j++){
    step = l/steps[sizes.size()-j];
    current_var=step*spacing[sizes.size()-j];
    backwards.push_back(current_var);
    l=l%steps[sizes.size()-j];
  }
  reverse(backwards.begin(),backwards.end());
  int dim=backwards.size();
  DataMesh<double> coordinate({dim});
  for (int i=0; i<dim; i++){
    coordinate.set_single_value(i,backwards[i]);
  }
  coords.push_back(coordinate);
}

void Patch::produce_coords(const int i,const int Boundary){
  int l=i, step,length;
  double current_var;
  vector <double> backwards;
  vector<int> sizes = Getnumofextents();
  length=sizes.size();
  for (int j=1; j<=length;j++){
    step = l/steps[sizes.size()-j];
    current_var=(step-Boundary)*spacing[sizes.size()-j];
    backwards.push_back(current_var);
    l=l%steps[sizes.size()-j];
  }
  reverse(backwards.begin(),backwards.end());
  int dim=backwards.size();
  DataMesh<double> coordinate({dim});
  for (int i=0; i<dim; i++){
    coordinate.set_single_value(i,backwards[i]);
  }
  coords.push_back(coordinate);
}

vector < double> Patch::coordinate(const int i){
  int dim = steps.size();
  vector<double> result;
  for (int j=0; j<dim; j++){
    result.push_back(coords[i].get_single_value(j));
  }
  return result;
}
