
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


bool voting_readcount(std::istream& r_cnt, int& total_cnt) {
    r_cnt >> total_cnt;
    return true;
}

bool voting_read(std::istream& r, int& total_cnt, int& can_cnt, string names[], vector<deque<int>>& ballots) {
    
    r >> total_cnt;
    r >> can_cnt;
    getline(r, names[0]);
    for (int i = 0; i < can_cnt; i++) {
 		getline(r, names[i]);
 		//cout << "candidate name is: " << names[i] << endl;
    }
    
  	string next;
  	int rowindex = 0;
  	
    while (getline(r, next)) {
    	cout << "vote preference: " << next << endl;
    	std::istringstream readvote(next);	
    	
    	int p;
    	int columnindex = 0;
    	//deque<int> vote;
    	while (readvote >> p) {
    		
    		//int pref;
    		//readvote >> pref;	
    		cout << "single vote preference: " << p << endl;				
    		ballots[rowindex].push_back(p);
    		//vote.push_back(p);	
    		cout << "ballot vote: " << ballots[rowindex][columnindex] << endl;	
 			columnindex++;   		
    	}	
    	//ballots.push_back(vote);
		rowindex++;
    }
    return true;
}


void voting_print( string ar[], int len) {
	for (int i = 0; i < len; i++) {
		cout << ar[i] << endl;
	}
}
void voting_print2d(vector<deque<int>>& ballots)  {
	
	vector< deque<int> >::iterator it1;
	deque<int>::iterator it2;
	
	for (it1 = ballots.begin(); it1 != ballots.end(); ++it1 ) {

		for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
			cout << *it2 << " ";
		}
		cout <<endl;
	}
}
/*
int check_winner(int[] score) {
	return (0);
}
*/
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

