/*
Author: Orin Prindle/u1114639@utah.edu

Problem Set 1 - Programming Task:
Given a list of input, find if there are any anagrams within.
The given input's 1st line will contain n and k.
-n is the amount of words
	1 <= n <= 10_000
-k is the amount of letters per word
	1 <= k <= 1_000
-all words and letters will be lowercase

*Examples*

Input 1:
	4 2
	me
	em
	to
	by
Output 1: b/c "me" and "em" are anagrams
	1

Input 2:
	7 4
	tape
	rate
	tarp
	seat
	pate
	east
	pest
Output 2: b/c "tape" and "pate" and "seat" and "east" are anagrams
	2
*/
import java.util.*;

public class PS1{
	//public vars
	public List<String> words;
	public int anagramCount;

	//Constructors
	public PS1(){
		words = new ArrayList<String>();
		anagramCount = 0;
	}

	//**public methods
	public static void main(String[] args){
		//Create Scanner obj
		Scanner input = new Scanner(System.in);

		//get n and k for the for loops
		int n = input.nextInt();
		int k = input.nextInt();

		//create PS1 obj
		PS1 ps1 = new PS1();
		input.nextLine(); //no idea why this has to be here but it won't work otherwise lol

		//loop n times till we get all the words
		for(int i = 0; i < n; i++)
			ps1.words.add(input.nextLine());

		ps1.countAnagrams();
		System.out.println(ps1.anagramCount);
	}	

	//**private methods
	private void countAnagrams(){
		//create an anagrams map, keys will be sorted angrams (i.e. idea -> adei), values will be the number of anagrams
		HashMap<String, Integer> anagrams = new HashMap<String, Integer>();

		//loop over every word in words
		for(String word : words){
			//convert this word to a charArray and sort it
			char[] word_arr = word.toCharArray();
			Arrays.sort(word_arr);
			
			String sorted_word = String.valueOf(word_arr); // set charArray back to String

			//if anagrams !have sorted_word put a new key/value pair in the map showing 0 for how many anagrams there are
			//otherwise increment the value of sorted_word
			if(!anagrams.containsKey(sorted_word))
				anagrams.put(sorted_word, 0);
			else
				anagrams.put(sorted_word, anagrams.get(sorted_word) + 1);
		}

		//go back over the map and count each value > 0
		for(Map.Entry<String, Integer> entry : anagrams.entrySet()){
			if(entry.getValue() > 0)
				anagramCount++;
		}
	}
}