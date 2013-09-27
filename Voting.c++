
/*
 * Voting.c++
 *
 */

// includes
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream> // out
#include <string>

#include <vector>
#include <deque>

#include "Voting.h"

using namespace std;

//int score_card[candidate_cnt]; 
//int candidate_cnt = 20; // revert


bool voting_readcount(std::istream& r_cnt, int& elections_cnt) {
    r_cnt >> elections_cnt;
    return true;
}

bool voting_read(std::istream& r, int& elections_cnt, int& voters_cnt, int& can_cnt, string names[], vector<deque<int>>& ballots) {
    
    r >> elections_cnt;
    r >> can_cnt;
    getline(r, names[0]);
    for (int i = 0; i < can_cnt; i++) {
 		getline(r, names[i]);
 		//cout << "candidate name is: " << names[i] << endl;
    }
    
  	string next;
  	int rowindex = 0;
  	
    while (getline(r, next)) {
    	//cout << "vote preference: " << next << endl;
    	std::istringstream readvote(next);	
    	
    	int p;
    	int columnindex = 0;
    	//deque<int> vote;
    	while (readvote >> p) {
    		
    		ballots[rowindex].push_back(p);
 			columnindex++;   		
    	}	
		rowindex++;
    }
    
	voters_cnt = rowindex;
	ballots.resize(voters_cnt);
	return true;
}


void voting_print( string ar[], int len) {
	for (int i = 0; i < len; i++) {
		cout << ar[i] << endl;
	}
}
void voting_print2d(vector<deque<int>>& ballots)  {
	
	//cout << "ballots.size:" << ballots.size();
	vector< deque<int> >::iterator it1;
	deque<int>::iterator it2;
	
	for (it1 = ballots.begin(); it1 != ballots.end(); ++it1 ) {

		for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}

void check_winner(vector<deque<int>>& ballots, int candidate_votes [], int& voters_cnt, int& can_cnt, string names[] ) {

	bool tie = false;
	bool possible_tie = true;
	bool winner = false;
	int candidate_selected;
	int majority_winning = voters_cnt /2;
	
	int max_vote;
	int min_vote;	
	//a negative vote count means a candidate's votes have been distributed, because he was a loser	

	//cout << endl << "The candidate selected are: " ;
	for (int i = 0; i < voters_cnt; i++) {
		int candidate_selected  = ballots[i].at(0);
		//cout << candidate_selected << " ";
		candidate_votes[candidate_selected - 1]++;
		
	}
	
	while ( (tie== false) && (winner == false) ) {  // There is no winner or tie so far
		
		int max_vote = 0;
		int min_vote = 0;
		for (int i = 0; i < can_cnt; i++ ) {			// looking at each candidate's vote
			
			if (candidate_votes[i] > majority_winning) { 		// A candidate has well over half the votes
				winner = true;
				cout << names[i] << endl;
				break;
			}

			if (candidate_votes[i] > max_vote) {
				max_vote = candidate_votes[i];
			} else if (min_vote > candidate_votes[i] && candidate_votes[i] >=0 )  {		//negative votes count see cmt above
				min_vote = candidate_votes[i];
			}
			
		}
		
		if (min_vote == max_vote) {
			tie = true;
		}
	}
	
	for (int i = 0; i < can_cnt ; i++) {
		
		if (candidate_votes[i] == max_vote) {
			cout << names[i] << endl;
		}
		
	}

}
/*
void voting_solve(istream& r, ostream& o) {
	
	while (voting_read(r, int tot_cnt, int can_cnt, string names[], vector<deque<int>>& ballots)) {
		
	}
}
*/

/*
int main() {
    using namespace std;

    string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    cout << "main" << endl;
    return 0;
}
*/

