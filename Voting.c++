
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
	std::set<int> list_of_winners;

	addVote ( voters_cnt, candidate_votes, ballots);

	int max_vote = candidate_votes[0];
	int min_vote = candidate_votes[0];	

///*DEBUG*/  int round = 1;
	while ( (tie== false) && (winner == false) ) {  // There is no winner or tie so far

///*DEBUG*/		cout << "\nround " << round;
///*DEBUG*/	if (round ==1) cout << "\nRound " << round << " min_vote  is " << min_vote << ", majority_winning " << majority_winning << endl;				
		for (int i = 0; i < can_cnt; i++ ) {			// looking at each candidate's vote
			
			if (candidate_votes[i] > majority_winning) { 		// A candidate has well over half the votes
				winner = true;
				out << names[i] << endl;
				return;
			}

			if (candidate_votes[i] >= max_vote) {
///*DEBUG*/		if (round ==1) cout << "\nCandidate " << i+1 << " is going in the leading bucket";
				if (candidate_votes[i] > max_vote) {
					list_of_winners.clear();
				}
				list_of_winners.insert(i);
				max_vote = candidate_votes[i];

			}
///*DEBUG*/	if (round ==1) cout << "\nCandidate " << i+1 << " has " << candidate_votes[i] << " votes"; 
			if (candidate_votes[i] <= min_vote  && candidate_votes[i] >= 0 )  {  //negative votes count see cmt above
///*DEBUG*/		if (round ==1) cout << "\nCandidate " << i+1 << " is going in the losing bucket";				
				if (candidate_votes[i] < min_vote) {  		
///*DEBUG*/			if (round ==1) cout << ",alone in there "; 
					list_of_losers.clear();				// empty set before inserting, if the candidate has the lowest votes
				}
				
				list_of_losers.insert(i);
				min_vote = candidate_votes[i];
			}
		}
		
		int winners_cumul_vote_cnt  = 0 ; 			// total vote received by winners

		for (set<int>::iterator it = list_of_winners.begin(); it != list_of_winners.end(); it++) {
			winners_cumul_vote_cnt += candidate_votes[(*it)] ;		
		}
		if (winners_cumul_vote_cnt == (unsigned) voters_cnt) {
			tie = true;
			break;
		}




		 //No tie and no clear winner, redistributin the vote of the loser
		
		for (set<int>::iterator it = list_of_losers.begin(); it != list_of_losers.end(); it++) {
///*DEBUG*/	if (round ==1) cout << "candidate " << (*it)+1 << " is a loser";
///*DEBUG*/	if (round ==1) cout << "\nhe has " << candidate_votes[(*it)] << " votes\n";
			candidate_votes[(*it)]= -1;		//set the vote count of a losing candidate to -1 to spot a loser
		}

///*DEBUG*/	if (round ==1) return;
		for (int i = 0; i < voters_cnt; i++) {		
			int current_vote = ballots[i].at(0);
			if (list_of_losers.find(current_vote - 1) != list_of_losers.end())	{	// if the candidate voted for is in losing set
				while (list_of_losers.find(current_vote - 1) != list_of_losers.end()) {
					ballots[i].pop_front();
					current_vote = ballots[i].at(0);
				}
				candidate_votes[current_vote -1]++;
			}
		}
		min_vote = candidate_votes[*(list_of_winners.begin())];  // The new minimum is the nbr of vote of one winning candidate
		list_of_losers.clear();
///*DEBUG*/		if (round ==1)cout << "\nEnd of round " << round << ", after the ballots are reassigned, we have: \n";		
///*DEBUG*/		if (round ==1) voting_print2d(ballots);
///*DEBUG*/		if (round ==1) return;
///*DEBUG*/

///*DEBUG*/ round++;
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
