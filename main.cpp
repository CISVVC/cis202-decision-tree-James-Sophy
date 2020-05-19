/**
 * Filename: main.cpp
 * Description: word guessing program
 * Date: 16/5/20
 * Author: sophyj@student.vvc.edu
**/
/*
   This program will create a decision tree for an animal
   guessing game.

   
   Pseudocode has been added as a hint to help with developing this
   program
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

Binary_tree read(istream& in)
{
//   Note the stream is called in
//
//    declare data as string
//    declare level as integer
//    get level from stream
//    get line from stream and assign it to data
//    if level == -1
//        return Binary_tree();
//
//    declare left as a Binary_tree and assign it read(in) 
//      Note:  it is a recursive call
//
//    declare right as a Binary_tree and assign it to read(in)
//      Note:  it is a recursive call
//
//    return Binary_tree(data, left, right)
	std::string data;
	int level;
	std::getline(in, data);
	level = atoi(&data[0]);
	const char * data_str = data.c_str();
	while(!isalpha(*data_str) && data.length() > 2){
		data_str++;
	}
	data = data_str;
	if(level == -1) return Binary_tree();
	Binary_tree left = read(in);
	Binary_tree right = read(in);
	
	return Binary_tree(data, left, right);
}

void write(ostream& out, const Binary_tree& tree, int level)
{
//    if tree.empty()
//        output -1 + \n to out
//        return 
//    output level + ' ' + tree.data() + \n to out
//    call write (out, tree.left(), level + 1)
//    call write (out, tree.right(), level + 1)
	if(tree.empty()){
		out << "-1\n";
		return;
	}
	out << level << " " << tree.data() << "\n";
	write(out, tree.left(), level + 1);
	write(out, tree.right(), level + 1);
}

/*
 * helper function that will help with definite or indefinite 
 * articles in a string
 */
std::string article(const std::string& entry)
{
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos)
    {
        article =  "an";
    }
    return article;
}

int main(int argc,char **argv)
{
    string file;
    if(argc > 1)
    {     
        file = argv[1];
    } else {
        file = "questions.dat";
    }
    Binary_tree root;  
    // Strategy
    //  get the filename from the command line arguments
    //  open the file stream
    //  initialize the root Binary_tree variable with data from the 
    //  file stream to initialize the decision tree root by calling
    //  the read function
    //

    // declare a Binary_tree question_tree and set it to root
    // while not done
    //    declare a string called response
    //    declare a Binary_tree called left and set it to 
    //       question_tree.left()
    //
    //    declare a Binary_tree called right and set it to 
    //       question_tree.right()
    //
    //    if left.empty() and right.empty()
            // Add code here that will carry on something like the 
            // following dialog:
            //
            //  Is it a mammal? Y  
            //  Does it have stripes? N  
            //  Is it a pig? N  

            // get the response from the user and 
            // if it is correct,
            //     print  "I guessed it!"
            // else
            //    print "I give up. What is it?"
            //    if user enters A hamster  
            //    then
            //        print "Please give me a question that is true 
            //                  for a hamster and false for a pig."
            //        get the response from the user
            //             example user response: Is it small and cuddly?  
            //
            //        Insert a node into question_tree so that this 
            //        question is used in future dialogs:
            //
            // One strategy to consider is to implement a set method 
            //   in the Binary_tree called root
            //   the set method will set the data and the left and right 
            //   subtrees for the given root
            //
            //  Future dialog:
            //     print "May I try again? "
            //     get response
            //     if response is yes
            //         done = true
            //     else
            //         question_tree = root
      //  else
      //      do
      //        print Is it a question_tree.data()  (y/n): 
      //        get response
      //      while (response != y and response != n)

      //      if response is y
      //         question_tree = left;
      //      else
      //         question_tree = right;

    // When done, write the decision tree to the data file by calling
    // the write function so that the new
    // question and answer is added to the data file
    std::fstream in(file);
    root = read(in);
    Binary_tree question_tree = root;
    bool done = false;
    while (!done){
    	std::string response;
    	Binary_tree left = question_tree.left();
    	Binary_tree right = question_tree.right();
    	if(left.empty() && right.empty()){
    		do {
    			std::cout << "Is it a " << question_tree.data() << "? (y/n): ", std::cin >> response;
    		} while (response != "y" && response != "n");
    		if(response == "y"){
    			std::cout << "I guessed it!\n";
    		} else {
    			string question;
    			std::cout << "I give up. What is it?: ", std::cin >> response;
    			std::cout << "Please give me a question that is true for a " << response << " and false for a " << question_tree.data() << "\n";
    			do {
    				std::getline(std::cin, question);
    			} while(question.length() == 0);
    			question_tree.set(question, Binary_tree(response), Binary_tree(question_tree.data()));
    		}
    		do {
    			std::cout << "May I try again? (y/n): ", std::cin >> response;
    		} while(response != "y" && response != "n");
    		if(response == "y"){
    			question_tree = root;
    		} else {
    			done = true;
    		}
    	} else {
    		do {
    			std::cout << question_tree.data() << "(y/n): ", std::cin >> response;
    		} while (response != "y" && response != "n");
    		if(response == "y"){
    			question_tree = left;
    		} else {
    			question_tree = right;
    		}
    	}
    }
    //write function refuses to work and I can't figure out why
    //write(in, root, 0);
}
