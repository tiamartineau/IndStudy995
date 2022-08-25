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
 private:
  int dim, totalpoints;
  vector <int> size;
 public:
  Mesh();
  Mesh(const vector<int>numofextents);
  Mesh(const vector<int>numofextents,const int Bounds);
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
  DataMesh<T>(const int Bounds, const vector <int> numofextents);
  void SetBMask(const int Bounds, const vector <int> numofextents);
  void SetBoundaryFace(const DataMesh<T>& B, const int i);
  ~DataMesh<T>();
  DataMesh<T> operator+(const DataMesh<T>& a);
  void operator += (const DataMesh<T>& b);
  void set_single_value(const int i, const T& a);
  void operator * (const T a);
  T get_single_value(const int i)const;
  void Print()const;
};

class Patch: public Mesh{
 private:
  vector <double> lengths;
  vector <DataMesh<double>> coords;
  vector <double> spacing;
  vector <int> steps;
 public:
  Patch(const vector <int> numofextents, const  vector <double> bounds);
  Patch(const vector <int> numofextents, const  vector <double> bounds, const int Bounds);
  vector<double> get_bounds(void) const;
  vector<int> num_of_steps(void) const;
  void produce_coords(const int i);
  void produce_coords(const int i, const int Bounds);
  vector<double> coordinate(const int i);
};

class MoveBounds{
 private:
  int dim, totalpoints, Boundss;
  vector<int> extents_within;
  vector<int> steps;
  vector<vector<int>> grid;
 public:
  MoveBounds(const vector<int> numofextents, const int Bounds);
  void GeneratePeriodicB(const DataMesh<bool>& B,const DataMesh<double>& mesh_data);
  void use_boundary_condtns(DataMesh<double>& mesh_data);
  void use_boundary_condtns(vector<double>& mesh_data);
};

template <typename T> class ComputeRHS{
 private:
  int totalpoints, Boundss;
  vector <int> steps;
  vector<int> numofextentss;
 public:
  ComputeRHS();
  void FillComputeRHS(const vector<int> N, const int Bounds);
  T ThirdDerivative(const DataMesh<T>& U, const int i, const DataMesh<bool>& B);
  T ThirdDerivative(const vector<T>& U, const int i, const DataMesh<bool>& B);
  T burger(const T u) const;
  T advectionfl(const T u) const;
};

template <typename T> class  dtU{
 private:
  int totalpoints, Boundss, dim;
  vector <int> steps;
  vector<int> numofextentss;
  vector<vector<T>> left_right_fl;
  vector<vector<T>> Flux;
  vector<vector<T>> TB_fl;
  ComputeRHS<T> RHS;
 public:
  dtU(const vector <int> numofextents, const int Bounds);
  void RungeKutta3(const DataMesh<T>& U, const double dt, DataMesh<T>& dUt, const DataMesh<bool>& B, MoveBounds& BM);
  void RungeKutta3shock(const DataMesh<T>& U, const double dt, DataMesh<T>& dUt, const DataMesh<bool>& B, MoveBounds& BM, const vector<DataMesh<bool>>& BoundaryFace);
  void LR_fl_reconst(const vector<DataMesh<bool>>& BoundaryFace, const DataMesh<T>& U);
  void LR_fl_reconst(const vector<DataMesh<bool>>& BoundaryFace, const vector<T>& U);
  void FluxReconstructor(const vector<DataMesh<bool>>& BoundaryFace);
  void divFlux(const DataMesh<bool>& B,vector<T>& H);
  int sign(const T a) const;
  T MinMod(const T a, const T b, const T c) const;
};

#endif //defs
