
/*
 * Voting.h
 *
 */


// defines
#ifndef Voting_h
#define Voting_h

// includes
#include <iostream> // istream, ostream
#include <string>
#include <vector>
#include <deque>
#include <set>
using namespace std;

// ------------
// voting_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @param s a string array by reference
 * @param q a vector of deque by reference
 * @return true if that succeeds, false otherwise
 */
bool voting_read(std::istream&, int&, int&, string[], vector<deque<int> >& );

// -------------
// collatz_print
// -------------

/**
 * prints the values in i
 * @param i a string array
 * @param v the length of the array
 */
void voting_print(string[], int);

// -----------------------
// collatz_print2d
// -----------------------

/**
 * prints the values inside b
 * @param v a vector of deque
 */
void voting_print2d(vector<deque<int> >& );

// ----------------------
// voting_add_vote
// ----------------------

/**
 * reads two ints into i and j
 * @param i an int
 * @param j an int by reference
 * @param q a vector of deque by reference
 */
void add_vote(int, int[], vector<deque<int> >& );


// ----------------------
// voting_check_winner
// ----------------------

/**
 * process a vector of deque and check winner
 * @param r a  vector of deque
 * @param i an int by reference
 * @param j an int by reference
 * @param j an int by reference
 * @param s a string array by reference
 * @param q a vector of deque by reference
 * @param w a std::ostream
 */
void check_winner (vector<deque<int> >& ballots, int[], int&, int&, string[], ostream&);

// -------------
// voting_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve(istream& , ostream& );


#endif // Voting_h

