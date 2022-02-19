/* C++ Assignment #2
 * Orin Prindle, u1114639, orin.prindle@gmail.com
 * 2/1/2021 @ 1:28pm
 *   -assignment created
 *   -filled in the constructors
 *   -added the get methods
 *
 * This will implement the given function declarations in pntvec.h
 */

//Necessary for printing
#include <iostream>
//Necessary for sqrt/pow
#include <math.h>

//Declarations are in a header file
//3 doubles, x, y, z
//going to be overloading most operators and functions on this obj
#include "pntvec.h"

//Constructors
/* Default Constructor -- this will create a defualt pntvec obj
 *
 * Parameters:
 *   n/a
 */
pntvec::pntvec(){
  x = 0;
  y = 0;
  z = 0;
}

/* Point Constructor -- this will create a pntvec obj given three input
 * 
 * Parameters:
 *  x_ - the given x point
 *  y_ - the given y point
 *  z_ - the given z point
 */
pntvec::pntvec(double x_, double y_, double z_){
  x = x_;
  y = y_;
  z = z_;
} 

/* Copy Constructor -- this will create a pntvec obj based off of a pntvec obj
 * 
 * Parameters:
 *  point - the given point
 */
pntvec::pntvec(const pntvec &point){
  x = point.x;
  y = point.y;
  z = point.z;
}

//Operator Overloads
/* Operator Overload = -- this will allow a user to write "pntvec_1 = pntvec_2;"
 *
 * Parameters:
 *   rhs - the righ hand side of the "=" operator
 */
pntvec& pntvec::operator= (const pntvec& rhs){
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;
 
  return *this;
}

/* Overload + -- this will allow a user to write "pntvec_1 = pntvec_1 + pntvec_2;"
 * 
 * Parameters:
 *   rhs - the right hand side of the "+" operator
 *
 * Returns:
 *   a new pntvec object that has accomplished the addition operation
 */
pntvec pntvec::operator+ (const pntvec& rhs) const{
  return pntvec(x+rhs.x, y+rhs.y, z+rhs.z);
}

/* Overload - -- this will allow a user to write "pntvec_1 = pntvec_1 - pntvec_2;"
 *
 * Parameters:
 *   rhs - the right hand side of the "-" operator
 * 
 * Returns:
 *   a new pntvec object that has accomplished the subtraction operation
 */
pntvec pntvec::operator- (const pntvec& rhs) const{
  return pntvec(x-rhs.x, y-rhs.y, z-rhs.z);
}

/* Overload * -- this will allow a user to write "pntvec_1 = pntvec_1 * pntvec_2;"
 *
 * Parameters:
 *   rhs - the right hand side of the "*" operator
 *
 * Returns:
 *   a new pntvec object that has accomplished the multiplication operation
 */
pntvec pntvec::operator* (const double& rhs) const{
  return pntvec(x*rhs, y*rhs, z*rhs);
}

/* Overload - -- this will allow a user to write "pntvec_1 = -pntvec_1;"
 *
 * Parameters:
 *   n/a
 *
 * Returns:
 *   a new pntvec object that has accomplished the negator operation
 */
pntvec pntvec::operator-() const{
  return pntvec(-x, -y, -z);
}

//Overload non-member Functions
/* Overload << -- this will allow a user to write "out << pntvec_1;"
 *
 * Parameters:
 *   out - the ostream that will be returned
 *   pnt - the pntvec obj that needs to be printed
 *
 * Returns:
 *   the pntvec obj in string form
 */
std::ostream& operator<< (std::ostream& out, const pntvec& pnt){
  out << "(" << pnt.x << ", " << pnt.y << ", " << pnt.z << ")";
  return out;
}

/* Overload >> -- this will allow a user to write "in >> pntvec_1;"
 * 
 * Parameters:
 *   in - the istream that will be returned
 *   pnt - the pntvec obj to be filled
 *
 * Returns:
 *   //TODO:need to research more to understand what truly returning
 */
std::istream& operator>> (std::istream& in, pntvec& pnt){
  std::cout << "Please enter your x, y, and z coordinates respectively: ";
  in >> pnt.x >> pnt.y >> pnt.z;
  return in;
}

//Get Functions
/* get_x -- gets x coordinate from this pntvec
 *
 * Returns:
 *   x - the x corrdinate from this pntvec
 */
double pntvec::get_x() const{
  return x;
}

/* get_y -- gets the y coordinate from this pntvec
 *
 * Returns:
 *   y - the y coordinate from this pntvec
 */
double pntvec::get_y() const{
  return y;
}

/* get_z -- gets the z coordinate from this pntvec
 * 
 * Returns:
 *  z - the z coordniate from pntvec
 */
double pntvec::get_z() const{
  return z;
}

//Get distance to method
/* distance_to - will get the distance between two points
 *
 * Parameters:
 *   other - the other point that is given
 *
 * Returns:
 *   dist - the distance between this point and the other point
 */
double pntvec::distance_to(const pntvec& other) const{
  double change_in_x = x - other.x;
  double change_in_y = y - other.y;
  double change_in_z = z - other.z;

  return sqrt(pow(change_in_x, 2) + pow(change_in_y, 2) + pow(change_in_z, 2));
}

//Main
/* Main -- the application entry point
 * 
 * Parameters:
 *   n/a
 * 
 * Return value:
 *   n/a 
 *
int main(){
  pntvec p0;
  pntvec p1(1, 1, 1);
  pntvec p2(2, 2, 2);

  std::cout << "p0: " << p0.get_x() << ", " << p0.get_y() << ", " << p0.get_z() << std::endl;
  std::cout << "p1: " << p1.get_x() << ", " << p1.get_y() << ", " << p1.get_z() << std::endl;
  std::cout << "p2: " << p2.get_x() << ", " << p2.get_y() << ", " << p2.get_z() << std::endl;

  pntvec test_p = p2 = p1 = p0;
  double distance = p1.distance_to(p2);

  std::cout << "test_p: " << test_p.get_x() << ", " << test_p.get_y() << ", " << test_p.get_z() << std::endl;
  std::cout << "test_p test << output: " << test_p << std::endl;
  std::cout << "distance: " << distance << std::endl;

  pntvec in_p;
  std::cin >> in_p;
  std::cout << "in_p is: " << in_p << std::endl;

  return 0;
}
*/
