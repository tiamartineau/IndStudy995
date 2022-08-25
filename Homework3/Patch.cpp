#include "defs.hpp"

Patch::Patch(vector <int> numofextents, vector <double> bounds): Mesh(numofextents){
  lengths = bounds;
  int step;
  //a check:
  if ((bounds.size()-2*numofextents.size())!=0){
    cout << "size of boundaries must be > gridspace dims" << endl;
    exit(1);
  }
  //otherwise,
  steps.push_back(1);
  for (int d =0; d<numofextents.size(); d++){
    spacing.push_back((lengths[d*2+1]-lengths[d*2])/(numofextents[d]-1));
    step = 1;
    for (int c=0; c<=d; c++)
      step*=numofextents[c];
    steps.push_back(step);
  }
  int totalpoints=total_points();
  for (int d=0; d<totalpoints; d++){
    produce_coords(d);
  }
}

vector<double> Patch::get_bounds(){
  return lengths;
}

vector<int> Patch::num_of_steps(){
  return steps;
}

vector<double> Patch::gridpoint_spacing(){
  return spacing;
}

void Patch::produce_coords(const int d){
  int l=d, step,length;
  double current_var;
  vector <double> backwards;
  vector<int> sizes = GetExtents();
  length=sizes.size();
  for (int j=1; j<=length;j++){
    step = l/steps[sizes.size()-j];
    current_var=step*spacing[sizes.size()-j];
    backwards.push_back(current_var);
    l=l%steps[sizes.size()-j];
  }
  reverse(backwards.begin(),backwards.end());
  coords.push_back(backwards);
}

vector < double> Patch::retrieve_coords(const int d){
  return coords[d];
}
