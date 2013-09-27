
/*
 * RunVoting.c+=
 *
 */

/*
To run the program:
% g++ -pedantic -std=c++0x -Wall Voting.c++ RunVoting.c++ -o RunVoting
% valgrind RunVoting < RunVoting.in > RunVoting.out
*/

// defines
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// includes
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Voting.h"

// main
int main() {
    using namespace std;

    //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
	
   //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n";
    
    //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n2 3 1\n";
	
    //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n3 2 1\n3 1 2\n3 2 1\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n2 3 1\n1 2 3\n"; //should be a tie

	string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n3 2 1\n3 1 2\n1 2 3\n1 2 3\n2 3 1\n1 2 3\n2 3 1\n1 2 3\n"; //should be a loser: john doe


	std::istringstream r(ex);

    int elections_cnt = 0;	// number of elections
    int can_cnt = 0;	// Number of candidates for an election
    
	string names[20];
	int candidate_votes[20] = {0}; 
	int voters_cnt = 0;		// Number of voters (i.e. number of lines of votes)	

    vector<deque<int>> ballots(20);
    //voting_readcount(cin, elections_cnt);
	
	cin >> elections_cnt;
	//cout << elections_cnt; 
	while (elections_cnt > 0) {
		//cout << " election " << elections_cnt << endl;
		voting_read(cin, elections_cnt, voters_cnt, can_cnt, names, ballots);
		check_winner(ballots, candidate_votes, voters_cnt, can_cnt, names ); 
		
		// Reset variables for a new election
		elections_cnt--;
		std::fill_n(candidate_votes, 20,0);	//reinitialize list of candidates
		voters_cnt =0;
		can_cnt = 0;
		ballots.clear();
		ballots.resize(20);
		if (elections_cnt != 0) cout << endl;
	} 
    //cout << elections_cnt << endl;
    //cout << can_cnt << endl;
	//voting_print(names, can_cnt);
	//voting_print2d(ballots);
	
    return (0);
}
