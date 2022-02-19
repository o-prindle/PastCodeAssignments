/** A small program for generating test data for Problem Set #2
 * in CS 4150, Spring semester 2022.
 * 
 * Students may use this code in their own submissions; however,
 * students may not share this code.  (The code-sharing rule still
 * applies.)
 * 
 * @author Peter Jensen
 * @version January 21, 2022
 */
package ps02;

import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.util.Random;
import java.util.Scanner;

public class SolarDataMaker
{
	/**
	 * Application entry point.  If you'd like to use this code interactively,
	 * 
	 * @param args
	 */
	public static void main(String[] args)
	{
		// Make a scanner for gathering input.
		
		Scanner input = new Scanner (System.in);
		
		// Ask for array specifications.
		
		System.out.print ("How large would you like the array? ");
		int arraySize = input.nextInt();
		
		System.out.print ("How large can the values grow in the array? ");
		int maxValue = input.nextInt();
		
		System.out.print ("What random number seed would you like to use? ");
		long seed = input.nextInt();
		
		// Validate the input
		
		if (maxValue < arraySize)
		{
			System.out.println("The values must be allowed to be at least as large as the array size.");
			System.out.println("Program stopped.");
			return;
		}
		
		// Generate the array
		
		int[] r = generate(arraySize, maxValue, seed);
		
		// Output the array to the console.
		
		String result = "int[] r = new int[]{";
		String separator = "";
		for (int v : r)
		{
			result += separator + v;
			separator = ", ";
		}
		result += "};";
		
		System.out.println(result);
		
		// Print out the location of the min value.
		
		int i = bruteForceLocateMinimum(r);
		System.out.println("Minimum value is " + r[i] + " at location " + i + ".");

		// Test the test array generator.  Exit rudely on failure.
		
		validate(r);
		
		// Put it on the clipboard for easy pasting.  (May need to comment this out
		// if your system does not support clipboards.)
		
		// Uncomment if desired.
		
		//StringSelection stringSelection = new StringSelection(result);
		//Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		//clipboard.setContents(stringSelection, new ClipboardOwner() {public void lostOwnership(Clipboard arg0, Transferable arg1){}});
	}
	
	/**
	 * Generates an array with one increasing sequence followed by
	 * one decreasing sequence.  Values will be in the range 
	 * [1..maxValue], and maxValue must be at least as large
	 * as the array is long:  maxValue >= arraySize.  
	 * 
	 * @param arraySize the size of the array to generate
	 * @param maxValue  the value of the maximum value in the array
	 * @param seed      the seed for the random number generator (for repeatability)
	 * @return
	 */
	public static int[] generate(int arraySize, int maxValue, long seed)
	{
		// Set up random number generator.
		
		Random rand = new Random(seed);
		
		// Make the array.
		
		int[] r = new int[arraySize];
		
		// Select minimum and maximum locations, must be different
		
		int minLoc, maxLoc;
		do
		{
			minLoc = rand.nextInt(arraySize);
			maxLoc = rand.nextInt(arraySize);
		} while (minLoc == maxLoc);
		
		//System.out.println(minLoc + " " + maxLoc);
		
		// Select minimum value, must be at least arraySize-1 less than maxValue.
		
		int minValue = rand.nextInt(maxValue-arraySize+1) + 1;
		
		// Put in the minimum;
		
		r[minLoc] = minValue;
		//System.out.println("- " + minLoc + " " + r[minLoc]);
		
		// Fill in the range between the minimum and maximum positions.
		
		int prevValue = r[minLoc];
		int loc = (minLoc+1) % arraySize;
		while (loc != maxLoc)
		{
			// Choose an amount to increase
			
			int stepsLeft = (maxLoc - loc + 1 + arraySize) % arraySize;
			int rangeLeft = (maxValue - prevValue);
			int increase  = rand.nextInt(rangeLeft/stepsLeft)+1;
						
			// Put the next value in the array, advance.
			
			r[loc] = prevValue + increase;
			//System.out.println("> " + loc + " " + r[loc] + " " + increase + " " + stepsLeft + " " + rangeLeft);
			
			prevValue = r[loc];
			loc = (loc + 1) % arraySize;
		}
		
		// Put in the maximum.
		
		r[maxLoc] = maxValue;
		//System.out.println("+ " + loc + " " + r[loc]);
		
		// Keep going, fill in the range between the maximum and minimum positions.
		
		prevValue = r[maxLoc];
		loc = (maxLoc+1)  % arraySize;
		while (loc != minLoc)
		{
			// Choose an amount to decrease
			
			int stepsLeft = (minLoc - loc + 1 + arraySize) % arraySize;
			int rangeLeft = -(minValue - prevValue);
			int decrease  = rand.nextInt(rangeLeft/stepsLeft)+1;
			
			
			// Put the next value in the array, advance.
			
			r[loc] = prevValue - decrease;
			//System.out.println("< " + loc + " " + r[loc] + " " + decrease + " " + stepsLeft + " " + rangeLeft);
			
			prevValue = r[loc];
			loc = (loc + 1) % arraySize;
		}
		
		// Done, return the array.
		
		return r;		
	}

	/**
	 * For testing, I needed a very simple way of locating the minimum.
	 * While this is not nearly efficient enough for the solution,
	 * it's an easy way to get an accurate answer for testing.
	 * 
	 * @param r any array
	 * @return the location of the minimum value in the array (zero-based)
	 */
	public static int bruteForceLocateMinimum(int[] r)
	{
		int minLoc = 0;
		for (int i = 0; i < r.length; i++)
			if (r[i] < r[minLoc])
				minLoc = i;
		return minLoc;
	}
	
	/**
	 * For testing, I needed a very simple way of locating the maximum.
	 * 
	 * @param r any array
	 * @return the location of the maximum value in the array (zero-based)
	 */
	public static int bruteForceLocateMaximum(int[] r)
	{
		int maxLoc = 0;
		for (int i = 0; i < r.length; i++)
			if (r[i] > r[maxLoc])
				maxLoc = i;
		return maxLoc;
	}
	
	
	/**
	 * Ensures the array meets the problem specification.  Rudely
	 * exits on failure.  While I hope students don't encounter
	 * these errors, this code will help guarantee that my tester
	 * is only using valid arrays.
	 * 
	 * @param r an array that should meet the problem #2 specification
	 */
	public static void validate (int[] r)
	{
		// Locate min and max values.
		
		int minLoc = bruteForceLocateMinimum(r);
		int maxLoc = bruteForceLocateMaximum(r);
		
		// Check min and max values.
		
		if (minLoc == maxLoc)
			throw new RuntimeException("Minimum and maximum locations are the same: " + minLoc);
		if (r[minLoc] < 1)
			throw new RuntimeException("Minimum value too small: " + r[minLoc]);
		if (r[maxLoc] > 1_000_000_000)
			throw new RuntimeException("Maximum value too large: " + r[maxLoc]);
		
		// Walk the from min to max, make sure it's strictly increasing.
		
		int prevValue = r[minLoc];
		int loc = minLoc;
		while (loc != maxLoc)
		{
			loc = (loc + 1) % r.length;
			if (r[loc] <= prevValue)
				throw new RuntimeException("Increasing sequence has non-increasing step: " + prevValue + " " + r[loc]);
			prevValue = r[loc];
		}
		
		// Keep walking from max to min, make sure it's strictly decreasing.
		
		while (loc != minLoc)
		{
			loc = (loc + 1) % r.length;
			if (r[loc] >= prevValue)
				throw new RuntimeException("Decreasing sequence has non-decreasing step." + prevValue + " " + r[loc]);
			prevValue = r[loc];
		}
		
		// If we get to the end of validate without throwing an exception, 
		//    the array is probably good.
	}
	
	
	
	
}
