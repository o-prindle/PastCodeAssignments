
/*
Author: Orin Prindle - u1114639

CS4150 - Algorithms

Problem Set 3 - Pier to Pier
	Basically just find most efficient places to put restraunts
	Not really sure what else to put here, I'm writing this after I finished lol
	
	Input:
		8 12
		1 2
		1 6
		1 8
		2 3
		2 6
		3 4
		3 5
		4 5
		4 7
		5 6
		6 7
		6 8
	Output:
		2
		1 4
*/
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

class PS3{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);

		//get the first line and parse it
		String first_line = input.nextLine();				
		String[] n_r = first_line.trim().split("\\s+");
		int n = Integer.parseInt(n_r[0]);
		int r = Integer.parseInt(n_r[1]);

		//create the _routes
		long[] _routes = new long[n+1];
		try {
			//put the routes into _routes
			for(int i = 1; i <= r; i++){
				//get and parse the new line
				String line = input.nextLine();
				String[] main_connection = line.trim().split("\\s+");
				int main = Integer.parseInt(main_connection[0]);
				int connection = Integer.parseInt(main_connection[1]);
	
				
				//apply the new line to the _routes
				_routes[main] = (_routes[main] | (1L << connection));
				//apply the reverse new line to the _routes
				_routes[connection] = (_routes[connection] | (1L << main));
			}
		} 
		catch(Exception e) { /*if there's no input then every island needs a restraunt*/ }
		
		//add the fact that routes connect to themselves
		for(int i = 1; i <= n; i++)
			_routes[i] = (_routes[i] | (1L << i));

		//run ps3
		PS3 ps3 = new PS3(_routes, n);
		ps3.ferryFinder(0, 0, 0, 0, 0, 0, 1);
		ps3.printDestinations();
	}

	//private vars
	private long[] routes;	//used to store all routes (Key=Main_Island,Value=Connecting_Islands)
	private long solution;	//used to store all solution (Key={1,2,3,...,s},Value=RestrauntIslands (where s = the amount of solution))
	private int solution_size;							//the current index within the solution HashMap
	private int n;											//the number of islands
	private long n_bin;										//the number of islands stored in a boolean arr masquerading as a long
	
	//constructor
	public PS3(long[] _routes, int _n){
		routes = _routes;		
		n = _n;	

		solution = 0;
		solution_size = 0;

		for(long i = 1; i <= n; i++){
			n_bin = n_bin | (1L << i);
		}
	}

	//public methods
	/* ferryFinder(long, long, long, long, int)

			parameters:
				long coveredIslands - will be a long containing the islands within 1 ferry away from the restraunt islands
								    - treated like an array. every bit from 1 - 36 represents n number of islands
				long restrauntIslands - these are all the islands that will have a restraunt on them
				long prevCI - the previous iteration of the coveredIslands
				long prevRI - the previous iteration of the restrauntIslands
				int i - the iterator that checks through the routes HashMap
			returns:
				void

		This method will use backtracking to try out all possible solution and put the successful ones into the solution HashMap. 
		Hopefully it'll work :)
	*/
	public void ferryFinder(long coveredIslands, long restrauntIslands, long prevCI, long prevRI, int RIsize, int prevRIsize, int i){
		//if max size combinations is less than n, return;
		if(solution_size != 0 && RIsize >= solution_size)
			return;
		//if every island is covered by a restraunt island
		if(coveredIslands == n_bin){ 
			//if this RI is less than the current solution
			if(solution_size == 0 || RIsize < solution_size) {
				solution = restrauntIslands;
				solution_size = RIsize;
			}
			return;
		}
		//if we have gotten to this point and i > n
		if(i > n)
			return;//then this is a failed solution


		//loop over every island within routes[i] (i.e. get every island that this, i, island is connected to)
			if((routes[i] | coveredIslands) > coveredIslands) {
				//otherwise add route_island to coveredIslands and add i to restrauntIslands
				coveredIslands = coveredIslands | routes[i];
				restrauntIslands = restrauntIslands | (1L << i);
			}
		
		//if coveredIslands already contains i+1, then we don't need to go down that tree
//		while((coveredIslands & (1L << i+1)) != 0)
//			i++;
		
		//if nothing's changed from the previous loop, then prune this side
		if(coveredIslands != prevCI && restrauntIslands != prevRI)
			ferryFinder(coveredIslands, restrauntIslands, coveredIslands, restrauntIslands, RIsize+1, RIsize+1, i+1); //check with this iteration
		ferryFinder(prevCI, prevRI, prevCI, prevRI, prevRIsize, prevRIsize, i+1); //check without this iteration
	}

	//will print the n_minimal destinations
	public void printDestinations(){
		// int smallest = 1;
		// for(int i = 2; i < solution.size(); i++)
		// 	if(solution.get(i).size() < solution.get(smallest).size())
		// 		smallest = i;

		System.out.println(solution_size);
		for(int i = 1; i <= n; i++)
			if((solution & (1L << i)) != 0)
				System.out.print(i + " ");
	}
}