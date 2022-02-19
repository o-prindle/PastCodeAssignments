/* This node class is used to build linked lists for the
 * string_set class.  
 *
 * Peter Jensen
 * February 12, 2021
 *
 * Edited/Filled in by:
 * Orin Prindle
 * February 16, 2021
 */

#include "node.h"

// By default, functions are not in a namespace.  They are not in any
// class.  Symbols defined here are globally available.  We need to
// qualify our function names so that you are definining our 
// cs3505::node class functions.  
//
// Note that you can also use the namespace cs3505 { } block, this 
// would eliminate one level of name qualification.  The 
// 'using' statement will not help in this situation.
// 
// Qualify it as shown here for functions: 
//      cs3505::node::functionname, etc.

/*******************************************************
 * node class - member function definitions
 ***************************************************** */

// Students will decide how to implement the constructor, 
// destructor, and any helper methods.

namespace cs3505{

  /* Constructor -- will take a string to create a new vector
   *
   * Parameters:
   *  d - a string that will represent data
   */
  node::node(bool isSentinel, int max_width, const std::string &d){
    data = d;
    constructVector(isSentinel, max_width);
  }

  /* Copy Constructor -- will take a node to create a new node
   *
   * Parameters:
   *  n - the given node
   */
  node::node(node *n){
    data = n->data;
    next_vec = n->next_vec;
  }

  /* Deconstructor -- how this object will be deleted
   */
  node::~node(){
    next_vec.clear();
    data.clear();
  }

  /* flip - will return true or false
   */
  bool node::flip(){
    int rng = rand();
    return rng%2 == 0;
  }

  /* constructVector - will add necessary length to vector
   *
   * Parameters:
   *  isSentinel - will determine whether or not to construct a sentinel vector
   */
  void node::constructVector(bool isSentinel, int max_width){
    if(isSentinel)
      for(int x = 0; x < max_width; x++)
	next_vec.push_back(NULL);
    else
      for(int x = 0; x < max_width; x++)
	if(next_vec.size() < 1)
	  next_vec.push_back(NULL);
	else if(flip() == true)
	  next_vec.push_back(NULL);
  }

}
