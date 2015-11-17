#ifndef BOGSOLVER_H
#define BOGSOLVER_H

#include "BogWordList.h"
#include "Dictionary.h"

//
// A class to solve boggle puzzles
//  The class reads in a dictionary and a board
//  Then solves it.
//  Once it has solved it, the solver can be
//  asked for the words it found, can be asked to print the words
//  with their locations, and to print the words just as strings
//

class BogSolver
{
    public:
	BogSolver();
	~BogSolver();
	bool readDict();
	bool readBoard();
	bool solve();			// search board for words in dict
	int  numWords();		// returns number of words found
	int  numWords(int len);		// number of words of length len
	BogWordList* getWords();	// returns all words found
	BogWordList* getWords(int len);	// returns words of len len
	void printWords();		// print all words in HBF
	void printWords(int len);	// print len-length words in HBF
	void listWords();		// print just the text, no coords
	void listWords(int len);	// just the text, no coords

   private:
	Dictionary dict;		// must use a Dictionary
	Dictionary solutionDict; // dict of solutions
	BogWordList bboard; 	// 2d vector for Boggle board
	BogWordList solutionList; // list of solutions
	BogWordList solListNoDup; // list of solutions with no duplicates
	vector<int> solutionLen;  // vector of lengths of solutions
	int rows, cols;			// dimensions of board
	bool solve(BogWord solu, string word, int x, int y); // recursive solving
};
#endif
