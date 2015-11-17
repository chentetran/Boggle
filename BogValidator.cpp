// Implementation of BogValidator class

#include "BogValidator.h"
#include "BogWordList.h"
#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

// constructor
BogValidator::BogValidator(){
	// nothing to do
}

// destructor
BogValidator::~BogValidator(){
	// nothing to do
}

// reads in the Dictionary
// returns true if successful, false otherwise
bool BogValidator::readDict(){
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

// reads in the board and calls solve()
// returns true
bool BogValidator::readBoard(){
	// read in size and letters 
	cin >> rows >> cols;
	for(int i=0; i<rows; i++){
		BogWord word;
		for(int j=0; j<cols; j++){
			char input;
			BogLett lett;
			cin >> input;
			input = toupper(input);
			lett.c = input;
			lett.row = i;
			lett.col = j;
			word.push_back(lett);
		}
		bboard.push_back(word);
	}

	return solve(); // makes list of all correct solutions
}

// returns true if s is valid
// false otherwise
bool BogValidator::isValid(string s){
	if((int)s.size() < 3) return false; // word too short

	if(validList.isWord(s)) return true;

	return false;
}

// checks if w is a duplicate
// returns isValid(w.s)
bool BogValidator::isValid(Words w){
	if(w.twice) return false;
	return isValid(w.s);
}

// Validates cin. End of input will return NULL to cin
void BogValidator::checkWords(){
	string word;
	while(cin >> word){ 	// take input from cin	
		for(int k=0;k<(int)word.size();k++) // convert to uppercase
			word[k] = toupper(word[k]);
		Words w;
		w.s = word;
		w.twice = false;
		userWords.push_back(w);	   // records user's solutions
	}

	bool valid;

	// print solutions (and their validity)
	for(int i=0; i!=(int)userWords.size(); i++){
		for(int j=0; j<(int)userWords.size(); j++){
			if(userWords[i].s == userWords[j].s && i!=j){
				userWords[j].twice = true;
			}
		}

		valid = isValid(userWords[i]);
		if(valid){
			cout << "OK " << userWords[i].s;
		}
		else{
			cout << "NO " << userWords[i].s;
		}
		cout << endl;
	}
}

// calls recursive function to solve
// returns true 
bool BogValidator::solve(){
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			BogWord solution;
			string word = "";
			solve(solution,word,i,j);
		}
	}
	return true;
}

// recursively solves the board, adds solutions to validList
// returns true if successful, false otherwise
bool BogValidator::solve(BogWord solution, string word, int x, int y){
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

	if(dict.isWord(word)){ // solution is in dictionary
			validList.insert(word);
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
