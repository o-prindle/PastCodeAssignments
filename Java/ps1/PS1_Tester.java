import java.io.File;  // Import the File class
import java.io.IOException;  // Import the IOException class to handle errors
import java.io.FileWriter;
import java.util.*;

public class PS1_Tester {
  	//public vars
	public int n;
	public int k;

	//private vars
    private String AlphaNumericString = "abcdefghijklmnopqrstuvxyz"; // chose a Character random from this String

  	public static void main(String[] args) {
    	System.out.println("Please select a test choice:");
    	System.out.println("1) Random");
    	System.out.println("2) Curated");

    	Scanner scan = new Scanner(System.in);
    	String fileName = "sampleTextFile.txt";
    	PS1_Tester tester = new PS1_Tester();

    	if(scan.nextInt() == 1){
    		tester.createTextFile(fileName);
  			tester.getNK();
  			tester.writeToTextFile(fileName);
    	}
    	else if(scan.nextInt() == 2){
    		fileName = "testList.txt";
    		tester.writeToTextFile(fileName);
    	}
  	}


	  public void createTextFile(String fileName){
	    try {
	      File textFile = new File(fileName);
	      if (textFile.createNewFile()) {
	        System.out.println("File created: " + textFile.getName());
	      } else {
	        System.out.println("File already exists.");
	      }
	    } 
	    catch (IOException e) {
	      System.out.println("An error occurred.");
	      e.printStackTrace();
	    }
	  }

	  public void writeToTextFile(String fileName){
	    try {
	      FileWriter writer = new FileWriter(fileName);
	      StringBuilder sb = new StringBuilder(k);

	      writer.write(n + " " + k + "\n");

	      for(int i = 0; i < n; i++){
	      	for(int j = 0; j < k; j++){
		      	// generate a random number between
	            // 0 to AlphaNumericString variable length
	            int index
	          		= (int)(AlphaNumericString.length()
	                        * Math.random());
	          	// add Character one by one in end of sb
	            sb.append(AlphaNumericString
	                          .charAt(index));

	            
        	}	
        	writer.write(sb.toString() + "\n");
        	sb = new StringBuilder(k);
	      }

	      writer.close();
	      System.out.println("Successfully wrote to the file.");
	    } 
	    catch (IOException e) {
	      System.out.println("An error occurred.");
	      e.printStackTrace();
	    }
	  }

	  public void getNK(){
	  	//get n and k
	    Scanner input = new Scanner(System.in);
	    System.out.println("Please enter in n and k:");
	    n = input.nextInt();
	    k = input.nextInt();
	  }

}