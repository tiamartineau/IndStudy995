#ifndef defs
#define defs

#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <math.h>

#define PI 3.14159
using namespace std;

//all class definitions in this file
//-----------------------------------------------------------

class Mesh{
 private:
  int dim, totalpoints;
  vector <int> size;
 public:
  Mesh();
  Mesh(const vector<int>numofextents);
  Mesh(const vector<int>numofextents,const int Boundary);
  int GetDim(void)const;
  vector <int> Getnumofextents(void)const;
  int GetNpoints(void)const;
};

template <typename T> class DataMesh: public Mesh{
 private:
  vector <T> mesh_data;
  vector <int> steps;
 public:
  DataMesh<T>();
  DataMesh<T>(const vector <int> numofextents, const T f);
  DataMesh<T>(const vector <int> numofextents);
  DataMesh<T>(const int Boundary, const vector <int> numofextents);
  void SetBMask(const int Boundary, const vector <int> numofextents);
  void SetBoundaryFace(const DataMesh<T>& Bound, const int i);
  ~DataMesh<T>();
  DataMesh<T> operator+(const DataMesh<T>& a);
  void operator += (const DataMesh<T>& b);
  void set_single_value(const int i, const T& a);
  void operator * (const T a);
  T get_single_value(const int i)const;
  int get_size()const;
  void Print();
};

class Patch: public Mesh{
 private:
  vector <double> bounds;
  vector <DataMesh<double>> coords;
  vector <double> spacing;
  vector <int> steps;
 public:
  Patch(const vector <int> numofextents, const  vector <double> bounds);
  Patch(const vector <int> numofextents, const  vector <double> bounds, const int Boundary);
  vector<double> get_bounds(void) const;
  vector<int> num_of_steps(void) const;
  void produce_coords(const int i);
  void produce_coords(const int i, const int Boundary);
  vector<double> coordinate(const int i);
};

class MoveBoundary{
private:
  int dim, totalpoints, Boundaries;
  vector<int> InternalSize;
  vector<int> steps;
  vector<vector<int>> grid;
public:
  MoveBoundary(const vector<int> numofextents, const int Boundary);
  void PeriodicBoundaries(const DataMesh<bool>& Bound,const DataMesh<double>& mesh_data);
  void usePeriodicBoundaryCondtns(DataMesh<double>& mesh_data);
  void usePeriodicBoundaryCondtns(vector<double>& mesh_data);
};

template <typename T> class ComputeRHS{
 private:
  int totalpoints;
  vector <int> steps;
  vector<int> Sizes;
 public:
  ComputeRHS();
  void FillInRHS(const vector<int> N,const int Boundary);
  T Flux(const DataMesh<T>& U, const int i,const  DataMesh<bool>& Bound);
  T Flux(const vector<T>& U, const int i,const  DataMesh<bool>& Bound);
  T burger(const T u) const;
};

template <typename T> class  dtU{
 private:
  int totalpoints, Boundaries, dim;
  vector <int> steps;
  vector<vector<T>> FluxLR;
  vector<vector<T>> Flux;
  vector<vector<T>> ULR;
  ComputeRHS<T> RHS;
 public:
  dtU(const vector <int> numofextents,const int Boundary);
  void RungeKutta3(const DataMesh<T>& U, const double dt, DataMesh<T>& dUt,const DataMesh<bool>& Bound, MoveBoundary& BM,const vector<DataMesh<bool>>& BoundaryFace);
  void FluxLeftRight(const vector<DataMesh<bool>>& BoundaryFace, const DataMesh<T>& U);
  void FluxLeftRight(const vector<DataMesh<bool>>& BoundaryFace, const vector<T>& U);
  void RebuildFlux(const vector<DataMesh<bool>>& BoundaryFace);
  void dFlux(const DataMesh<bool>& Bound,vector<T>& H);
  int sign(const T a) const;
};

#endif //defs
