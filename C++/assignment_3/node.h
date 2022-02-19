/* This node class is used to build drop lists for the
 * string_set class.
 *
 * Created by: Peter Jensen
 * February 12, 2021
 * 
 * Edited and filled out by: Orin Prindle
 * February 16, 2021
 */

// Guard against double inclusion

#ifndef NODE_H
#define NODE_H

// You will use strings, and you may use vectors.
#include <string>   //for data
#include <vector>   //for links to other nodes
#include <cstdlib>  //for rand
#include <iostream> //for printing

namespace cs3505
{
  // We're in a namespace - declarations will be within this CS3505 
  // namespace.  (There are no definitions here, see node.cpp.)

  /* Node class for holding elements. */

  /* Note:  Do not alter the next line of code.  My tester will 
   * re-write the 'class node ' to 'class node : private auditor' 
   * so that it inherits from my auditing class (harmlessly). 
   */

  class node 
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data and constructor within this class.

    private:
      std::string data; //Used to hold the node's data
      std::vector<node*> next_vec; //Used to hold the next-node references
      
      node(bool isSentinel, int max_width, const std::string &d); //Constructor
      node(node* n); //copy Constructor
      ~node(); //Destructor

      void constructVector(bool isSentinel, int max_width); //Will add necessary length to vector
      bool flip(); //Will return true or false;
  };
}
		
#endif 
	
