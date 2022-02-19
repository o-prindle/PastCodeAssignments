/*
Author: Orin Prindle/u1114639@utah.edu

Problem Set 2 - Programming Task: Solar Minimum

Use SolarDataMaker.java to test this file.

Given a circular array of numbers [7, 10, 12, 9, 7, 2, 1, 2, 4, 5]
find the minimum point within.
	-data values will be ints ranging from [1...10^9]
	-number of records will be [2...10^9]
	-data record's indexes start at 0

We will be provided a single int on line one that will represent the number of records:
	1250
This will indicate a data set of R[0]...R[1249]
We should be issuing numbers of in this form: 
	query 123
where 123 is the index for the data you will get
When we find the minimum value print data as such:
	minimum 189
*/

import java.util.Scanner;
import java.lang.Math;
import java.util.*;

public class PS2{

	//private vars
	private int data_length;
	private Scanner in;
	private Hashtable<Integer, Integer> known_data;

	public PS2(int rl){
		data_length = rl;
		in = new Scanner(System.in);
		known_data = new Hashtable<>();
	}

	public static void main(String[] args){
		Scanner main_scan = new Scanner(System.in);

		PS2 ps2 = new PS2(main_scan.nextInt());

		System.out.println("minimum " + ps2.findMinimum(0, ps2.data_length, 1_000_000_001, true));
	}

	private int findMinimum(int begindex, int endex, int previous_pivot_value, boolean whichWay){
		//setup indexes
		int pivot = begindex + ((endex - begindex)/2); 
		int left = pivot-1;
		int right = pivot+1;

		//if left or right's indexes go out of bounds, loop around
		if(left < 0)
			left = data_length-1;
		if(right > data_length-1)
			right = 0;

		//setup  values
		int left_value;
		int pivot_value;
		int right_value;
		if(!known_data.containsKey(left))
			known_data.put(left, getValue(left));
		if(!known_data.containsKey(pivot))
			known_data.put(pivot, getValue(pivot));
		if(!known_data.containsKey(right))
			known_data.put(right, getValue(right));
		left_value = known_data.get(left);
		pivot_value = known_data.get(pivot);
		right_value = known_data.get(right);

		//base case
		if(pivot_value < left_value && pivot_value < right_value)
			return pivot;

		//odd cases
		if(pivot_value > previous_pivot_value && whichWay == true)    //if this pivot value is > previous value and we went left,
			return findMinimum(pivot+1, endex, pivot_value, false);   //go right
		if(pivot_value > previous_pivot_value && whichWay == false)   //if this pivot value is > previous value and we went right,
			return findMinimum(begindex, pivot-1, pivot_value, true); //go left

		//can't seem to find a better solution cases :(
		if(pivot == 0 || pivot == data_length-1)
			return iterateFindMin(pivot);

		//iteration for recursion
		if(left_value < pivot_value)
			return findMinimum(begindex, pivot-1, pivot_value, true);
		else
			return findMinimum(pivot+1, endex, pivot_value, false);
		


		//IF IT'S RECURSIVE IT'LL WORK BETTER
		/*
		I've reached a point where a case is completely unsolvable with my current iteration
		If I managed to convert this to recursion, when we find a max, we're gonna go down both left and right sides then compare them in the end. 
		We return the value that is 


		Work around for peak maybe?
		If peak is on the left side then we have to go right
		if peak is on the right side then we  have to left

		Work around for multiple in a row?
		If there are multiple in a row, then iterate begindex or endex 
		to the point where another number goes above or below it


		*/

		//set the indexes
		// begindex = 0;
		// endex = data_length;

		// //set all indexes to their desired numbers
		// pntr_index = begindex + ((endex - begindex)/2);
		// left_index = pntr_index - 1;
		// right_index = pntr_index + 1;


		// //set all values to their desired numbers
		// pntr_value = getValue(pntr_index);
		// left_value = getValue(left_index);
		// right_value = getValue(right_index);

		// //While pntr_value is not less than left_value and right_value
		// while(!(pntr_value < left_value && pntr_value < right_value)){
		// 	//set the next area of array to check
		// 	if(left_value > pntr_value)
		// 		begindex = pntr_index;
		// 	else
		// 		endex = pntr_index+1;

		// 	pntr_index = begindex + ((endex - begindex)/2);

		// 	//THIS BELOW ME DON'T WORK THE LEFT SIDE
		// 	//ITS CAUSED BY LINE 70
		// 	//GOTTA FIGURE A WAY TO MAKE data_length CHANGE TO GET THE CURRENT LENGTH WE ARE LOOKGIN AT
		// 	//check to make sure the pntr_index isn't the first or last index in r
		// 	if(pntr_index == 0 || pntr_index == data_length-1)
		// 		break;

		// 	//set the other pntrs
		// 	left_index = pntr_index - 1;
		// 	right_index = pntr_index + 1;

		// 	//set r_length
		// 	//we do this here bc the loop is on it's next iteration
		// 	//r_length = Math.ceil(r_length/2);

		// 	//set all values to their desired numbers
		// 	pntr_value = getValue(pntr_index);
		// 	left_value = getValue(left_index);
		// 	right_value = getValue(right_index);
			
		// }

		// return pntr_index;
	}

	private int getValue(int index){
		System.out.println("query " + index);
		return in.nextInt();
	}

	private int iterateFindMin(int pivot_index){
		int key;
		int next_key;
		if(pivot_index == 0){
			for(int i = data_length-1; i >= 0; i--){
				key = i;
				next_key = key-1;
				if(!known_data.containsKey(key))
					known_data.put(key, getValue(key));
				if(!known_data.containsKey(next_key))
					known_data.put(next_key, getValue(next_key));

				if(known_data.get(key) < known_data.get(next_key))
					return key;
			}
		}
		else{
			for(int j = 0; j < data_length; j++){
				key = j;
				next_key = key+1;
				if(!known_data.containsKey(key))
					known_data.put(key, getValue(key));
				if(!known_data.containsKey(next_key))
					known_data.put(next_key, getValue(next_key));

				if(known_data.get(key) < known_data.get(next_key))
					return key;
			}
		}
		return -1;
	}
}