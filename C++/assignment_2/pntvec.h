/* A pntvec is a c-style data structure that represents
 * a 3D point or vector:
 * 
 * pntvec(x,y,z);
 * 
 * 
 * Note: DO NOT COMPILE THIS FILE DIRECTLY
 * 
 * 
 * Orin Prindle, u1114639, orin.prindle@gmail.com 
 * 2/1/2021 @ 1:07pm
 *   -pntvec.h created
 *   -added constructors
 */

//allows access to in/out streams
#include <iostream>

class pntvec{
  
 private: //Declarations below for private variables and functions
  //Variables
  double x, y, z;

 public: //Declarations below for public constructors, destructors, functions and variables
  //Constructors
  pntvec();//Default
  pntvec(double x_, double y_, double z_);//Point
  pntvec(const pntvec &point);//Copy

  //Overload Operator Functions
  pntvec& operator= (const pntvec& rhs);//assignment 
  pntvec operator+ (const pntvec& rhs) const;//addition
  pntvec operator- (const pntvec& rhs) const;//subtraction
  pntvec operator* (const double& scalar) const;//multiplication
  pntvec operator- () const;//negator

  //Overload non-member Functions
  friend std::ostream& operator<< (std::ostream& out, const pntvec& pnt);//supports streaming out a pntvec
  friend std::istream& operator>> (std::istream& in, pntvec& pnt);//supports streaming in a pntvec

  //Get functions  
  double get_x() const;
  double get_y() const;
  double get_z() const;

  //Get distance to function
  double distance_to(const pntvec& other) const;

};//trailing semi-colon necessary
