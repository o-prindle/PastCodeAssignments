/* Testing file for pntvec objects
 * Orin Prindle - u1114639 - orin.prindle@gmail.com
 * 2/4/2021 @ 2:45pm
 *   -file created
 *
 */

//allows for printing to console
#include <iostream>

//
#include "pntvec.h"

/* check_validity -- will compare a pntvec to given doubles
 *
 * Parameters:
 *   pnt - the pntvec obj being checked
 *   x - the x to compare to pntvec.x
 *   y - the y to compare to pntvec.y
 *   z - the z to compare to pntvec.z
 *
 * Returns:
 *   correct - the boolean value determining if pntvec is valid
 */
bool check_validity(pntvec pnt, double x, double y, double z){
  bool correct = true;
  if(pnt.get_x() != x)
    correct = false;
  else if(pnt.get_y() != y)
    correct = false;
  else if(pnt.get_z() != z)
    correct = false;

  return correct;
}

/* st_DefaultConstructor -- will simply test the default constructor
 *
 * Parameters:
 *   n/a
 *
 * Returns:
 *   a boolean value
 */
bool st_DefaultConstructor(){
  pntvec pnt;
  
  return check_validity(pnt, 0, 0, 0);
}

/* st_PointConstructor -- will simply test the point constructor
 *
 * Parameters:
 *   x - the given x point
 *   y - the given y point
 *   z - the given z point
 *
 * Returns:
 *   a boolean value
 */
bool st_PointConstructor(double x, double y, double z){
  pntvec pnt(x, y, z);
  
  return check_validity(pnt, x, y, z);
}

/* st_PointConstructor -- will simply test the point constructor
 *
 * Parameters:
 *   x - the given x point
 *   y - the given y point
 *   z - the given z point
 *
 * Returns:
 *   a boolean value
 */
bool st_CopyConstructor(pntvec p){
  pntvec pnt(p);
  
  return check_validity(pnt, p.get_x(), p.get_y(), p.get_z());
}

/* main -- the application entry point
 *
 * Parameters:
 *   n/a
 *
 * Returns:
 *   report_error - returns -1 if there is an error 0 otherwise
 */
int main(){
  int report_error = 0;

  //simply test default constructor
  if(!st_DefaultConstructor()){
    std::cout << "Error in st_DefaultConstructor()" << std::endl;
    report_error = -1;
  }

  //simply test point constructor
  if(!st_PointConstructor(1, 2, 3)){
    std::cout << "Error in st_PointConstructor(double, double, double)" << std::endl;
    report_error = -1;
  }

  //simply test copy constructor
  pntvec p(1, 2, 3);
  if(!st_CopyConstructor(p)){
    std::cout << "Error in st_CopyConstructor(pntvec)" << std::endl;
    report_error = -1;
  }
  
  if(report_error == 0)
    std::cout << "No errors" << std::endl;
  return report_error;
}
