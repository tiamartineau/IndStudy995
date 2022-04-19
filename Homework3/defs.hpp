#ifndef defs_hpp
#define defs_hpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

//Mesh:
class Mesh{
public:
  Mesh(int dims, std::vector<int> extents);
  //dimensions of mesh
  int dimensions(void);
  //number of points along each dimension
  std::vector<int>extents(void);
  //total overall # of pts
  int total_points(void);
  std::vector<int> ext;
  int dims;
private:
  //initially tried to inclued dims, extents
  //called elsewhere, required to move them to public... oops
  int totalpoints;
};

//DataMesh
template <class T> class DataMesh : public Mesh{
public:
  DataMesh(int dimensions, std::vector<int> extents);
  //to set individual values
  void set_values(std::vector<T> fill_data);
  //retrieving those values
  std::vector<T> retrieve_values(void);
  //to set 1 specific value
  void set_single_value(int coordinate, T data);
  //to retrieve 1 specific value
  T get_single_value(int coordinate);
  //to retrieve total # of points
  int get_all_points(void);
  void print_datamesh(void);
  void operator +=(DataMesh<T> overload);
  DataMesh<T> operator +(DataMesh<T> overload);
  void operator *=(T overload_x);
private:
  //mesh data cannot be touched
  std::vector<T> mesh_data;
};


#endif
