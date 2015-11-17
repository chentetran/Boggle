#ifndef BOGSCORER_H
#define BOGSCORER_H

#include "BogWordList.h"
#include "Dictionary.h"

struct Words
{
	string s;						// user entered solutions
	bool valid;						// tracks if solution is valid
	int score;						// score of the word
};

//
//  A class to score the boggle solutions.
//	Reads a checker report.
// 	Assigns a score to each word based on word length and validity
// 	Allows for printing validity, word, and score.
//

class BogScorer
{
public:
	BogScorer();  // constructor
	~BogScorer(); // destructor
	bool readAnswers();
	void scoreAnswers();
	void printAnswers();

private:
	Dictionary solutionDict;		// dictionary of solutions
	vector<Words> userWords;		// vector of user entered solutions
	vector<Words> userWordsNoDup;	// vector of solutions no duplicates
	bool isValid(Words w);			// validates one word
	int total;						// total score
};

#endif