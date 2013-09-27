
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

bool voting_readcount(std::istream&, int&);

bool voting_read(std::istream&, int&, int&, int&, string[], vector<deque<int>>& ballots);

void voting_print(string[], int);

void voting_print2d(vector<deque<int>>& ballots);

void check_winner (vector<deque<int>>& ballots, int[], int&, int&, string[]);
int main();



#endif // Voting_h

