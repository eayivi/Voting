
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
    
    //r >> elections_cnt;
    r >> can_cnt;
    getline(r, names[0]);
    for (int i = 0; i < can_cnt; i++) {
 		getline(r, names[i]);
 		//cout << "candidate name is: " << names[i] << endl;
    }
	//cout << endl << "cancidates are: " << endl;
	//voting_print(names, can_cnt);  
  	string next;
  	int rowindex = 0;
    while (getline(r, next)) {
    	//cout << "vote preference: " << next << endl;
    	if (next.empty()) break;
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
    //cout << "ballots are: " << endl;
	//voting_print2d(ballots);
	voters_cnt = rowindex;
	ballots.resize(voters_cnt);
	//cout << endl << "Reading of election " << elections_cnt << " done successfully" << endl;
	return true;
}


void voting_print( string ar[], int len) {
	for (int i = 0; i < len; i++) {
		cout << ar[i] << endl;
	}
}
void voting_print2d(vector<deque<int>>& ballots)  {
	
	cout << "ballots.size:" << ballots.size() << endl;
	vector< deque<int> >::iterator it1;
	deque<int>::iterator it2;
	
	for (it1 = ballots.begin(); it1 != ballots.end(); ++it1 ) {

		for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
			cout << *it2 << "|";
		}
		cout << endl;
	}
}

void check_winner(vector<deque<int>>& ballots, int candidate_votes [], int& voters_cnt, int& can_cnt, string names[] ) {
	
	//cout << endl << "Entering Check Winner " << endl;
	bool tie = false;
	bool winner = false;
	int majority_winning = voters_cnt /2;
	cout << endl << "There are " << voters_cnt << " voters";
	
	std::set<int> list_of_losers;
	//a negative vote count means a candidate's votes have been distributed, because he was a loser	

	//cout << endl << "The candidate selected are: " ;
	for (int i = 0; i < voters_cnt; i++) {						// looking through a round
		
		cout << endl << "Looking through round  for voter" << i << endl;
		int candidate_selected  = ballots[i].at(0);
		//cout << candidate_selected << " ";
		cout << "They selected candidate " << candidate_selected << endl;
		candidate_votes[candidate_selected - 1]++;
		cout << "There are " << voters_cnt << " voters";
	}
	cout << "after round check";
	int max_vote = candidate_votes[0];
	int min_vote = candidate_votes[0];	
	
	while ( (tie== false) && (winner == false) ) {  // There is no winner or tie so far
		
		
		for (int i = 0; i < can_cnt; i++ ) {			// looking at each candidate's vote
			
			if (candidate_votes[i] > majority_winning) { 		// A candidate has well over half the votes
				winner = true;
				cout << names[i] << endl;
				return;
			}

			if (candidate_votes[i] > max_vote) {
				max_vote = candidate_votes[i];
			} else if (candidate_votes[i] <= min_vote  && candidate_votes[i] >=0 )  {  //negative votes count see cmt above
				
				if (candidate_votes[i] < min_vote) {  		
					list_of_losers.clear();				// empty set before inserting, if the candidate has the lowest votes
				}
				
				list_of_losers.insert(i);
				min_vote = candidate_votes[i];
			}
		}
		
		if (min_vote == max_vote) {			// this indicates a tie
			//cout << "min_vote == max_vote";
			tie = true;
			break;				
		}

		 //No tie and no clear winner, redistributin the vote of the loser
		
		for (set<int>::iterator it = list_of_losers.begin(); it != list_of_losers.end(); it++) {
   			//cout << "losers: " << *it;
			candidate_votes[(*it)-1]= -1;		//set the vote count of a losing candidate to -1 to spot a loser
		}
		for (int i = 0; i < voters_cnt; i++) {
				//cout << " reallocating ballots, i is " << i << endl;
				int current_vote = ballots[i].at(0);
				//cout << endl << "current vote is " << current_vote;
				while (list_of_losers.find(current_vote - 1) != list_of_losers.end()) {// if the candidate voted for is in losing set
					//cout << endl << "voter " << i << "'s " << "first choice will be eliminated, i.e. value: "; 
					//cout << ballots[i].front();
					ballots[i].pop_front();
					current_vote = ballots[i].at(0);
				}
				candidate_votes[current_vote -1]++;
		}
		//cout << "New content is: " << endl;
		// Printing content of remaining ballots
		/*    
		vector< deque<int> >::iterator it1;
		deque<int>::iterator it2;
	
		for (it1 = ballots.begin(); it1 != ballots.end(); ++it1 ) {

			for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
				cout << *it2 << " ";
				//cout << endl << "wait" << endl;
			}
			cout << endl;
		}
		*/	
		min_vote = max_vote;
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

