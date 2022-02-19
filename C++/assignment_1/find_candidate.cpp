/* C++ Assignment #1
 * Orin Prindle, u1114639, orin.prindle@gmail.com
 * 1/22/2021 @ 11:31am
 *  -assignment created
 *  -added includes, main, and forward decs
 * 1/23/2021 @ 10:20am
 *   -filled out generate_distance, generate_score
 *   -created fill_vector, takes input from a file and fills a vector<pntvec>
 * 1/24/2021 @ 10:46am
 *   -finished the logic of calculating the best score in the main method
 */

//created for console I/O
#include <iostream>
//created for file I/O
#include <fstream>
//created for string I/O
#include <sstream>
//allows for string fuctions to be used
#include <string>

//Vector class works similarly to arraylists in other langs
//use 'push_back' to append items to a vector
//access like an array
#include <vector>

//declarations are in a header file
//3 doubles x, y, z as points 
#include "pntvec.h"

/* Putting the Main Method at the top of the file, and will need
 * helper methods. Therefore declaring all helper methods before main.
 */
double generate_distance(pntvec candidate, pntvec point);
double generate_score(pntvec candidate, std::vector<pntvec> points);
std::vector<pntvec> fill_vector(std::string file_name);

/* Main -- the application entry point
 * 
 * Parameters:
 *   n/a
 *
 * Return value:
 *   an integer exit code, return non-zero if error occured
 */
int main(){
  //created a vector obj to hold all candidates/point_cloud
  std::vector<pntvec> candidates;
  std::vector<pntvec> point_cloud;

  //Call fill_vector to fill in the candidates/point_cloud vector
  candidates = fill_vector("candidates.txt");
  point_cloud = fill_vector("point_cloud.txt");

  //Check to see if the vectors are filled
  if(candidates.size() < 1)
    return 22;
  if(point_cloud.size() < 1)
    return 22;

  //creates a pntvec that will hold the best candidate
  pntvec bs_point = candidates[0];
  //creates a double to hold the best score
  double best_score = generate_score(candidates[0], point_cloud);

  //this will do the actual computation to get the scores
  //in the event of a tie, choose the first candidate that was the best
  for(int i = 1; i < candidates.size(); i++){
    double current_score = generate_score(candidates[i], point_cloud);
    if(current_score < best_score){
      best_score = current_score;
      bs_point = candidates[i];
    }
  }

  //Prints out the lowest score on the first line,
  //then prints out the point on the second line
  std::cout << best_score << std::endl;
  std::cout << bs_point.x << ' ' << bs_point.y << ' ' << bs_point.z << std::endl;
  
  return 0;
} 

/* generate_score -- The for loop that will add up the point's score
 * 
 * Parameters:
 *   candidate - the original point to compare to all other points
 *   points - the list of points that the candidate needs to be compared to
 *  
 * Returns:
 *   the score of the candidate point
 */
double generate_score(pntvec candidate, std::vector<pntvec> points){
  double score = 0;

  for(int i = 0; i < points.size(); i++)
    score += generate_distance(candidate, points[i]);

  return score;
}

/* generate_distance -- will take the two point and find the distance between them
 *
 * Parameters:
 *   candidate - the original point 
 *   point - the point we are trying to find the distance to
 *
 * Returns:
 *   the distance between the candidate and point
 */
double generate_distance(pntvec candidate, pntvec point){
  double change_in_x = candidate.x - point.x;
  double change_in_y = candidate.y - point.y;
  double change_in_z = candidate.z - point.z;

  return (change_in_x * change_in_x) + (change_in_y * change_in_y) + (change_in_z * change_in_z);
}

/* fill_vector -- will take a file and read thru it to fill in a vector obj
 *
 * Parameters:
 *   file_name - the name of the file to read from
 * 
 * Returns:
 *   the filled vector obj
 */
std::vector<pntvec> fill_vector(std::string file_name){
  //the vector to fill
  std::vector<pntvec> points;

  //open the file
  std::ifstream file(file_name.c_str());

  pntvec point;
  //go thru and read every point, ignore duplicates, in case of error
  //return 22;
  while(true){ 
    //parse through the file token, by token and put them into the point
    file >> point.x;
    if(file.fail())
      break;

    file >> point.y;
    if(file.fail())
      break;

    file >> point.z;
    if(file.fail())
      break;

    points.push_back(point);
  }

  file.close();

  return points;
}
