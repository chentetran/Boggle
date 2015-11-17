# ReadMe for COMP 15 HW6
## Boggle Assignment by Vincent Tran

1. This program simulates the word game Boggle.

2. List of files:
		BogWordList.h      - header file of BogWordList, BogWord, and BogLett
		BogSolver.h        - header file of BogSolver class
		BogSolver.cpp      - implementation of BogSolver 
		BogValidator.h     - header file of BogValidator class
		BogValidator.cpp   - implementation of BogValidator 
		BogScorer.h        - header file of BogScorer class
		BogScorer.cpp      - implementation of BogScorer
		Makefile           - for compiling
		solverMain.cpp     - main file for bbsolver program
		checkerMain.cpp    - main file for bbchecker program
		scorerMain.cpp     - main file for bbscorer program
		Dictionary.h       - header file of Dictionary class
		Dictionary.cpp     - implementation of Dictionary
		Node.h             - header file for Node class
		Node.cpp           - implementation of Node

3. To compile, use included Makefile.

4. Data structures used include vectors and tries.
	Vectors were used to make each BogWord and BogWordList.
	Tries were used in the Dictionary class to store words.

5. Nested for-loops were used to iterate through BogWordLists and access
		each BogLett. Also used to read in the Boggle board.
   While-loops were used to take in data from cin (for reading board and
   		getting input from user).

6. Special thanks to Vincent Tsang and Zach Kirsch for debugging suggestions.