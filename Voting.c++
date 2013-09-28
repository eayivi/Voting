
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
#include <stdexcept>
#include <vector>
#include <deque>
#include <algorithm>  // std::fill
#include <set>


using namespace std;

//int candidate_cnt;
//int score_card[20]; 

bool voting_readcount(std::istream& r_cnt, int& elections_cnt) {
    r_cnt >> elections_cnt;
    return true;
}

bool voting_read(std::istream& r, int& voters_cnt, int& can_cnt, string names[], vector<deque<int> >& ballots) {
    

    r >> can_cnt;
    getline(r, names[0]);
    for (int i = 0; i < can_cnt; i++) {
 		getline(r, names[i]);
    }
  	string next;
  	int rowindex = 0;
    while (getline(r, next)) {
    	if (next.empty()) break;
		std::istringstream readvote(next);	
		    	
    	int p;
    	int columnindex = 0;
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
void voting_print2d(vector<deque<int> >& ballots)  {
	
	vector< deque<int> >::iterator it1;
	deque<int>::iterator it2;
	
	for (it1 = ballots.begin(); it1 != ballots.end(); ++it1 ) {

		for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}

void addVote(int& vote_cnt, int candidate_votes [], vector<deque<int> > ballots) {
    int selection;
	for (int i = 0; i < vote_cnt ; i++) {
		selection  = ballots[i].front();
		int temp = candidate_votes[selection - 1];
		temp++;
		selection--;
		candidate_votes[selection] = temp;
	}
}

bool check_majority(const vector<deque<int> >& ballots, int candidate_votes [], int can_cnt, int vote_cnt) {

	int winner_index = -1;
	for (int i = 0; i < can_cnt; i++) {
		int can_score = candidate_votes[i];
		if (can_score > can_cnt / 2) {
			winner_index = i; 
			break;
		}
	}
	if (winner_index >= 0)
		return true;
	else 
		return false;
}

//void add_loser()

//void add_leader()

//void find_winner()

//void is_tie()

void check_winner(vector<deque<int> >& ballots, int candidate_votes [], int& voters_cnt, int& can_cnt, string names[], ostream& out ) {
	bool tie = false;
	bool winner = false;
	int majority_winning = voters_cnt /2;
	
	std::set<int> list_of_losers;

	addVote ( voters_cnt, candidate_votes, ballots);

	int max_vote = candidate_votes[0];
	int min_vote = candidate_votes[0];	
	while ( (tie== false) && (winner == false) ) {  // There is no winner or tie so far
				
		for (int i = 0; i < can_cnt; i++ ) {			// looking at each candidate's vote
			
			if (candidate_votes[i] > majority_winning) { 		// A candidate has well over half the votes
				winner = true;
				out << names[i] << endl;
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
			tie = true;
			break;				
		}

		 //No tie and no clear winner, redistributin the vote of the loser
		
		for (set<int>::iterator it = list_of_losers.begin(); it != list_of_losers.end(); it++) {
			candidate_votes[(*it)]= -1;		//set the vote count of a losing candidate to -1 to spot a loser
		}
		for (int i = 0; i < voters_cnt; i++) {
				int current_vote = ballots[i].at(0);
				
				while (list_of_losers.find(current_vote - 1) != list_of_losers.end()) {// if the candidate voted for is in losing set
					ballots[i].pop_front();
					current_vote = ballots[i].at(0);
				}
				candidate_votes[current_vote -1]++;
		}
		min_vote = max_vote;
	}
	
	for (int i = 0; i < can_cnt ; i++) {
		
		if (candidate_votes[i] == max_vote) {
			out << names[i] << endl;
		}
		
	}

}

void voting_solve(istream& r, ostream& out) {
    using namespace std;

    int elections_cnt = 0;  // number of elections
    int can_cnt = 0;    // Number of candidates for an election

    string names[20];
    int candidate_votes[20] = {0};
    int voters_cnt = 0;     // Number of voters (i.e. number of lines of votes) 

    vector<deque<int> > ballots(1000);

    r >> elections_cnt;

    int in = 0;
    while (in < elections_cnt) {

        voting_read(r, voters_cnt, can_cnt, names, ballots);
        
        check_winner(ballots, candidate_votes, voters_cnt, can_cnt, names, out );
    	

        // Reset variables for a new election
        std::fill_n(candidate_votes, 20,0); //reinitialize list of candidates
        voters_cnt =0;
        can_cnt = 0;
        ballots.clear();
        ballots.resize(1000);
        in++;
        if (in != elections_cnt) out << endl;
    }

}
