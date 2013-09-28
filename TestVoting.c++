
/*
 * TestVoting.c++
 * 
 */

/*
To Test the program:
% g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main
% valgrind TestVoting > TestVoting.out
*/

// includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include "gtest/gtest.h"
#include "Voting.h"

using namespace std;


// read
TEST(Voting, read_0) {
	//string ex = "1\n\n2\nRene Trevino\nEnam\n1 2\n1 2\n2 1\n";
    //!! Above line breaks, because voting_read cannot handle election count (unlike voting_solve)
	
    string ex = "2\nRene Trevino\nEnam\n1 2\n1 2\n2 1\n";
    std::istringstream r(ex);

	string names [20];
    vector<deque<int>> vect(5);

	//int tcnt = 0;  as above, cannot measure elections_counts with voting_read :)
	int ccnt = 0;
    int vcnt = 0;
	bool v = voting_read(r, vcnt, ccnt, names, vect);
	ASSERT_TRUE(v == true);
	ASSERT_TRUE(vcnt == 3);
	ASSERT_TRUE(ccnt == 2);
	

}

TEST(Voting, read_1) {

    string ex = "3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n"; 

    std::istringstream r(ex);

    string names [20];
    vector<deque<int>> vect(30);

    int ccnt = 0;
    int vcnt = 0;
    
    bool v = voting_read(r, vcnt, ccnt, names, vect);
    
    ASSERT_TRUE(v == true);
    ASSERT_TRUE(ccnt == 3);
    ASSERT_TRUE(vcnt == 5);
}

TEST(Voting, read_2) {

    string ex = "3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";
    std::istringstream r2(ex);

    string s [20];
    vector<deque<int>> vect(5);   

    int ccnt = 7;
    int vcnt = 9;

    bool v1 = voting_read(r2, vcnt, ccnt, s, vect);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(vcnt == 5);
    ASSERT_TRUE(ccnt == 3);
}


TEST(Voting, solve_0) {
    std::istringstream r("1\n\n3\nJohn Smith\nJane Doe\nJack Shepard\n1 2 3\n1 2 3\n1 3 2\n1 2 3\n1 3 2\n1 2 3\n");
    std::ostringstream w;

    voting_solve(r, w);

    ASSERT_TRUE(w.str() == "John Smith\n");  
}


//string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n";

    //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n2 3 1\n";

    //string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n3 2 1\n3 1 2\n3 2 1\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n2 3 1\n1 2 3\n"; //should be a tie
