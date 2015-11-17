// Implementation of BogSolver class

#include <vector>
#include <iostream>
#include "BogSolver.h"
#include "BogWordList.h"
#include <ctype.h>
#include <stdlib.h>

using namespace std;

// constructor
BogSolver::BogSolver(){
	// nothing to do
}

// destructor
BogSolver::~BogSolver(){
	// nothing to do
}

// reads in dictionary
// returns true if successful, false otherwise
bool BogSolver::readDict(){
	string word;
	while(cin >> word){
		if(word == ".") break; // end loop when sentinel
		for(int i=0;i<(int)word.size();i++) // convert to uppercase
			word[i] = toupper(word[i]);
		if(!dict.insert(word))
			return false;
	}
	return true;
}

// reads in board
// returns true if successful
bool BogSolver::readBoard(){
	// read in size and letters 
	cin >> rows >> cols;
	for(int i=0; i<rows; i++){
		BogWord word;
		for(int j=0; j<cols; j++){
			char input;
			BogLett lett;
			cin >> input;
			if(cin.eof()) exit(-1); // don't process invalid boards
			input = toupper(input); // convert to uppercase
			lett.c = input;
			lett.row = i;
			lett.col = j;
			word.push_back(lett);
		}
		bboard.push_back(word);
	}

	return true;
}

// calls recursive function to solve
// returns true
bool BogSolver::solve(){
	BogWord solution;
	string word = "";

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			solve(solution,word,i,j);
		}
	}
	return true;
}

// recurses through board to find solutions
// returns true if x is a valid solution
// false otherwise
bool BogSolver::solve(BogWord solution, string word, int x, int y){
	bool found = false;

	if(x < 0 || x >= rows) return false;
	if(y < 0 || y >= cols) return false;

	for(int i=0; i<(int)solution.size(); i++){ // check if tile already used
		if(bboard[x][y].row == solution[i].row && 
		   bboard[x][y].col == solution[i].col){
			return false;
		}
	}

	word += bboard[x][y].c;
	solution.push_back(bboard[x][y]);

	// turning Q into QU
	if(bboard[x][y].c == 'Q'){
		word += 'U';
		BogLett U;
		U.c = 'U';
		solution.push_back(U);
	}

	// solution is valid 
	if(dict.isWord(word)){ 
		// if not a duplicate, add to solListNoDup
		if(!solutionDict.isWord(word)){ 
			solListNoDup.push_back(solution);
		}
		solutionList.push_back(solution); // add to list of solutions
		solutionLen.push_back((int)solution.size());
		solutionDict.insert(word); // add to Dict of solutions
		found = true;
		
	}

	if(!dict.isPrefix(word)) return false; // not a prefix

	for(int i=x-1; i<=x+1; i++){
		for(int j=y-1; j<=y+1; j++){
			found = solve(solution,word,i,j);
		}
	}
	
	return found;
}

// returns number of words found
int BogSolver::numWords(){
	return (int)solListNoDup.size();
}

// returns numbers of words of length len
int BogSolver::numWords(int len){
	int numWords = 0;
	for(int i=0; i!=(int)solListNoDup.size(); i++){
		if((int)solListNoDup[i].size() == len)
			numWords++;
	}
	return numWords;
}

// returns all words found as a BogWordList*
BogWordList* BogSolver::getWords(){
	// Note: the caller is responsible for freeing this memory
	BogWordList *wordsList = new BogWordList;
	for(int i=0; i<(int)solListNoDup.size(); i++){
		BogWord word;
		for(int j=0; j<(int)solListNoDup[i].size(); j++){
			BogLett lett = solListNoDup[i][j];
			word.push_back(lett);
		}
		wordsList->push_back(word);
	}
	return wordsList;
}

// returns all words with length len as a BogWordList
BogWordList* BogSolver::getWords(int len){
	// Note: the caller is responsible for freeing this memory
	BogWordList *wordsList = new BogWordList;
	for(int i=0; i<(int)solListNoDup.size(); i++){
		if((int)solListNoDup[i].size() == len){
			BogWord word;
			for(int j=0; i<(int)solListNoDup[i].size(); j++){
				BogLett lett = solListNoDup[i][j];
				word.push_back(lett);
			}
			wordsList->push_back(word);
		}
	}
	return wordsList;
}

// prints the words in solutionList in HBF
void BogSolver::printWords(){
	for(int i=0; i!=(int)solutionList.size(); i++){
		// don't print 1-2 letter words;
		if((int)solutionList[i].size() < 3) continue;
		cout << "< ";
		for(int j=0; j!=(int)solutionList[i].size(); j++){
			if(solutionList[i][j].c == 'Q'){
				cout << solutionList[i][j].c
					 << 'U' 				   << " "
					 << solutionList[i][j].row << " "
					 << solutionList[i][j].col << " ";
				j++;
				continue;
			}
			cout << solutionList[i][j].c << " "
				 << solutionList[i][j].row << " "
				 << solutionList[i][j].col << " ";

		}
		cout << ">" << endl;
	}
	cout << "< >" << endl;
}

// prints the words in solutionList with length len in HBF
void BogSolver::printWords(int len){
	if(len < 3) return; // don't print 1-2 letter words;
	for(int i=0; i!=(int)solutionList.size(); i++){
		if(solutionLen[i] == len){ // check length
			cout << "< ";
			for(int j=0; j!=(int)solutionList[i].size(); j++){
				if(solutionList[i][j].c == 'Q'){
					cout << solutionList[i][j].c
						 << 'U'                    << " "
						 << solutionList[i][j].row << " "
						 << solutionList[i][j].col << " ";
					j++;
				}
				else{
					cout << solutionList[i][j].c << " "
						 << solutionList[i][j].row << " "
						 << solutionList[i][j].col << " ";
				}
			}
			cout << ">" << endl;
		}
	}
	cout << "< >";
}

// prints the words in solutionList
void BogSolver::listWords(){
	for(int i=0; i<(int)solListNoDup.size(); i++){
		// don't print 1-2 letter words
		if((int)solListNoDup[i].size() < 3) continue;
		for(int j=0; j<(int)solListNoDup[i].size(); j++){
			cout << solListNoDup[i][j].c;
		}
		cout << endl;
	}
}

// prints the words in solutionList with length len
void BogSolver::listWords(int len){
	for(int i=0; i<(int)solListNoDup.size(); i++){
		if((int)solListNoDup[i].size() == len){ // check length
			for(int j=0; j<(int)solListNoDup[i].size(); j++){
				cout << solListNoDup[i][j].c;
			}
			cout << endl;
		}
	}
}