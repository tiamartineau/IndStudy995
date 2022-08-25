#ifndef defs
#define defs

#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <math.h>

#define PI 3.14159
//I am finally no longer using "std::" for every
//cout, endl, vector, etc.
using namespace std;

class Mesh{
 public:
  Mesh(vector<int>numofextents);
  int GetDim(void);
  vector <int> GetExtents(void);
  int total_points(void);
 private:
  int dim, totalpoints;
  vector <int> size;
};

class Patch: public Mesh{
 public:
  Patch(vector <int> numofextents, vector <double> bounds);
  vector<double> get_bounds(void);
  vector<int> num_of_steps(void);
  void produce_coords(const int i);
  vector<double> gridpoint_spacing(void);
  vector < double> retrieve_coords(const int i);
 private:
  vector <double> lengths;
  //inside of the patch file, lengths = bounds
  vector<vector <double>> coords;
  vector <double> spacing;
  //variable "steps" below represents stencil steps
  //stencil steps are essentially a recalculation and
  //shift of those values, i.e. from cell center to
  //cell face, for example
  vector <int> steps;
};

template <typename T> class DataMesh: public Mesh{
 private:
  vector <T> mesh_data;
 public:
  DataMesh<T>(vector <int> numofextents, T f);
  DataMesh<T>(vector <int> numofextents);
  ~DataMesh<T>(void);
  DataMesh<T> operator+(const DataMesh<T>& a);
  void operator += (const DataMesh<T>& b);
  void operator * (const T a);
  void set_single_value (const int i, const T value);
  T get_single_value (const int i);
  void Print(void);
};


template <typename T> class ComputeRHS{
 private:
  int totalpoints;
  vector <T> derivative;
  //again, below, these 'steps' are stencil steps
  vector <int> steps;
 public:
  ComputeRHS(vector<int> N);
  //estimated spatial derivatives below (and RK3)
  void UpstreamDifferencing( DataMesh<T>& U, const double dt, DataMesh<T>& dtU);
  void DownstreamDifferencing( DataMesh<T>& U, const double dt, DataMesh<T>& dtU);
  void CenteredDifferencing( DataMesh<T>& U, const double dt, DataMesh<T>& dtU);
  void RungeKutta3 (DataMesh<T>& U, const double dt, DataMesh<T>& dtU);
  T ThirdDerivative(DataMesh<T>& U, const int i);
  T ThirdDerivative(vector<T>& U, const int i);
  //advection below is the flux for the advection problem
  T advection(const T u) const;
};



#endif //defs
