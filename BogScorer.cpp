// Implementation of BogScorer class

#include "BogScorer.h"
#include "BogWordList.h"
#include <iostream>
#include <vector>
#include "Dictionary.h"

using namespace std;

// constructor
BogScorer::BogScorer(){
	total = 0;
}

// destructor
BogScorer::~BogScorer(){
	// nothing to do
}

// reads in checker report
// returns true 
bool BogScorer::readAnswers(){
	string OK;
	string word;

	// take input from cin
	while(cin >> OK >> word){ 
		Words w;
		if(OK == "OK") w.valid = true;
		else if(OK == "NO") w.valid = false;
		else return false;
		w.s = word;
		if(!solutionDict.isWord(word) && w.valid){
			userWordsNoDup.push_back(w);
		}
		userWords.push_back(w);
		solutionDict.insert(word);
	}
	return true;
}

// assigns a score to each item in userWords
// Boggle scoring rules:
// 3-4 letter words = 1pt
// 5 letter words   = 2pts
// 6 letter words   = 3pts
// 7 letter words   = 5pts
// 8+ letters       = 11pts
void BogScorer::scoreAnswers(){
	for(int i=0; i<(int)userWords.size(); i++){
		if(userWords[i].valid){  // word is OK
			if((int)userWords[i].s.size() >= 8) // 8+ letters
				userWords[i].score = 11;
			else if((int)userWords[i].s.size() == 7) // 7 letters
				userWords[i].score = 5;
			else if((int)userWords[i].s.size() == 6) // 6 letters
				userWords[i].score = 3;
			else if((int)userWords[i].s.size() == 5) // 5 letters
				userWords[i].score = 2;
			else									 // 3-4 letters
				userWords[i].score = 1;
			total += userWords[i].score;
		}
		else{					 // word is NO
			userWords[i].score = 0;
		}
	}	
}

// prints solutions, their validity, and their score
void BogScorer::printAnswers(){
	for(int i=0; i<(int)userWords.size(); i++){
		cout << userWords[i].score << " ";
		if(userWords[i].valid)
			cout << "OK ";
		else cout << "NO ";
		cout << userWords[i].s << endl;
	}
	cout << userWordsNoDup.size() << " words " << total << " points" << endl;

}