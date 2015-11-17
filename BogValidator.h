#ifndef BOGVALIDATOR_H
#define BOGVALIDATOR_H

#include "Dictionary.h"
#include "BogWordList.h"

struct Words
{
	string s;						// user entered solutions
	bool twice;						// tracks if solution occurs twice
};

class BogValidator
{
public:
	BogValidator(); // constructor
	~BogValidator(); // destructor
	bool readDict(); // read in a dictionary
	bool readBoard(); // read in a board
	bool isValid(std::string s); // validates one word
	void checkWords(); // validates cin. The end of input will
			   // simply return NULL to cin.
private:
	Dictionary dict;				// dictionary of all words
	Dictionary validList;			// dict of all correct solutions
	BogWordList bboard; 			// 2d vector for Boggle board
	BogWordList userList;  			// list of user entered solutions
	vector<Words> userWords; 		// vector of user entered solutions
	int rows, cols; 		  		// dimensions of Boggle board
	bool solve(); 		  			// finds all solutions
	bool solve(BogWord bw, string s, int x, int y); // recursive solution
	bool isValid(Words w);			// checks validity of w
};



#endif

