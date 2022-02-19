/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are
 * O(lg size) on average.  The operator= and get_elements
 * functions are O(size).
 *
 * Peter Jensen
 * February 12, 2021
 *
 * Edited/Filled in by:
 * Orin Prindle
 * February 16, 2021
 */

#include "string_set.h"

namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */

  /** Constructor:  The parameter indicates the maximum
    * width of the next pointers in drop list nodes.
    */
  string_set::string_set(int max_width){
    //set instance variables
    this->max_width = max_width;
    this->head = new node(true, max_width, "");
    this->size = 0;
    srand(time(NULL)); //set rand()'s seed to time(NULL) for node.flip()
  }


  /** Copy constructor:  Initialize this set
    * to contain exactly the same elements
    * as another set.
    */
  string_set::string_set (const string_set &other){
    // this->head = NULL;
    *this = other;
    srand(time(NULL)); //set rand()'s seed to time(NULL) for node.flip()
  }


  /** Destructor:  Release any memory allocated
    * for this object.
    */
  string_set::~string_set(){
    clean(); //call clean to destruct this
  }

  /* Additional public and private helper function definitions needed here */

  /*** Public Mehtods ***/
  /* add - will take some string and input it into a node into the string_set
   *
   * Parameters:
   *  data - a reference to a string object
   */
  void string_set::add(const std::string &data){
    if(contains(data)) //if this contains data, don't add it
      return;

    //will keep track of all previous connecting nodes
    std::vector<node*> prior = get_prior(data);
    //this is the node to be inserted
    node *toInsert = new node(false, max_width, data);
    //set all of toInsert's pntrs to forward pointers
    for(int x = 0; x < toInsert->next_vec.size(); x++)
      if(prior[x] == NULL){ //if prior addr == NULL, set toInsert's next addr to NULL
        toInsert->next_vec[x] = NULL;
        prior[x] = toInsert;
      }
      else{ //otherwise, set it to the necessary addr
        toInsert->next_vec[x] = prior[x]->next_vec[x];
        prior[x]->next_vec[x] = toInsert;
      }

    size++; //increment size
  }

  /* remove - will take some string, find the corresponding node, and delete the node
   *
   * Parameters:
   *  data - a reference to a string object
   */
  void string_set::remove(const std::string &data){
    if(!contains(data)) //if this !contain data, don't remove it
       return;

    //will keep track of all previous connecting nodes
    std::vector<node*> prior = get_prior(data);
    //node to delete
    node* toDelete = prior[0]->next_vec[0];
    //set all of toInsert's pntrs to forward pointers
    for(int x = 0; x < toDelete->next_vec.size(); x++)
      if(prior[x] == NULL || prior[x]->next_vec[x] == NULL)//if this addr is NULL or the next addr is NULL, stop iter
        continue;
      else if(x < toDelete->next_vec.size())//if x < toDelete's next_vec's size, link to the toDelete->next_vec addr
        prior[x]->next_vec[x] = toDelete->next_vec[x];
      else //otherwise link to NULL
        prior[x]->next_vec[x] = NULL;

    //clear the next_vec and delete the obj
    delete toDelete;

    size--; //decrement size
  }

  /* contains - will take some string and and see if it is within the string_set
   *
   * Parameters:
   *  data - a reference to a string object
   *
   * Returns:
   *  bool - whether or not data is in the string_set
   */
  bool string_set::contains(const std::string &data) const{
    std::vector<node*> prior = get_prior(data);

    //if data's next is !NULL and prior.data == param data, return true, else false
    if(prior[0]->next_vec[0] != NULL && prior[0]->next_vec[0]->data.compare(data) == 0)
      return true;
    return false;
  }

  /* get_size - will get the length of the string_set
   *
   * Returns:
   *  int - the length of the string_set
   */
  int string_set::get_size() const{
    return size;
  }

  /* Operator Overload = - this will allow a user to write "string_set_1 = string_set_2"
   *
   * Parameters:
   *  rhs - the right-hand-side variable for this to be set to
   *
   * Returns:
   *  a new string_set which equals rhs
   */
  string_set& string_set::operator=(const string_set &rhs){
    //if they're == just return this one
    if(&rhs == this)
      return *this;

    //clean this string_set
    clean();

    //set other variables
    this->head = new node(true, max_width, "");
    this->size = 0;

    std::vector<std::string> rhs_elements = rhs.get_elements();
    for(int i = 0; i < rhs_elements.size(); i++)
      add(rhs_elements[i]);

    this->max_width = rhs.max_width;

    return *this;
  }

  /* get_elements - this will return all the elements in this string_set in ascending order
   *
   * Returns:
   *  A new vector reference
   */
  std::vector<std::string> string_set::get_elements() const{
    std::vector<std::string> vec(size, ""); //create return variable

    node *current = NULL;
    if(head != NULL && head->next_vec[0] != NULL)
      current = head->next_vec[0]; //create node iter
    int x = 0; //create vec iter

    //loop thru all nodes
    while(current != NULL){
      vec[x] = current->data; //set vec[x] to current's data
      current = current->next_vec[0]; //iterate node
      x++; //iterate vec
    }

    return vec;
  }

  /*** Private Helpers ***/
  /* clean - this method will remove all nodes from this string_set and reset all public variables
   */
  void string_set::clean(){
    if(head == NULL)
      return;
    
    node *current = head; //node iterator
    node *temp = NULL;

    //loop thru nodes, delete em
    while(current != NULL){
      temp = current->next_vec[0]; //set temp = next node
      delete current; //delete current
      current = temp; //current = temp for iter
    }

    //reset all variables
    head = NULL;
    size = 0;
    max_width = max_width;
  }

  /* get_prior - this method will get all previous nodes before data
   *
   * Parameters:
   *  data - this is the given data to get all previous nodes to
   *
   * Returns:
   *  *prior - the vector pointer that is prior
   */
  std::vector<node*>& string_set::get_prior(const std::string &data)const {
    std::vector<node*> *prior = new std::vector<node*>(max_width); //create return variable
    int x = max_width-1;  //prior/next_vec iterator
    node* current = head; //node iterator

    //loop thru the nodes/prior/next_vecs
    while(x >= 0){
      //if next == NULL or current data >= param data, set prior[x] to current x--
      if(current->next_vec[x] == NULL || current->next_vec[x]->data.compare(data) >= 0){
        prior->at(x) = current;
        x--;
        continue;
      }
      current = current->next_vec[x]; //iterate thru the nodes
    }

    return *prior;
  }
}
