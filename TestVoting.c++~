
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

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

//string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n"; 


// read
TEST(Voting, read_0) {
	string ex = "1\n\n2\nRene Trevino\nEnam\n1 2\n1 2\n2 1\n";
	std::istringstream r(ex);
	
	string names;
	
	deque<int>> sample(1,2,3);
	deque<int>> sample2(5,6,8);

	vector<deque<int>> vec(sample1, sample2);
	
	int tcnt = 0;
	int ccnt = 0;
	bool v = voting_read(r, tcnt, ccnt, names, vec);
	ASSERT_TRUE(v == true);
	ASSERT_TRUE(tcnt == 1);
	ASSERT_TRUE(ccnt == 2);
	

}

TEST(Voting, read_1) {

    string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n"; 

    std::istringstream r(ex);

    int tcnt = 0;
    int ncnt = 0;
    const bool v1 = voting_readcount(r, tcnt);
    
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(tcnt == 1);
    //ASSERT_TRUE(ncnt == 3);
}

TEST(Voting, read_2) {

    string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";

    std::istringstream r2(ex);
    int t_cnt = 0;
    int c_cnt = 0;
    string s = "";
    int v = 0;
    
    bool v1 = voting_read(r2, t_cnt, c_cnt, s, v);
    ASSERT_TRUE(v1 == true);
    ASSERT_TRUE(t_cnt == 1);
    ASSERT_TRUE(c_cnt == 3);
    ASSERT_TRUE(s == "John Doe");
}

