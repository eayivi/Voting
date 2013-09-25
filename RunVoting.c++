
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

#include "Voting.h"

// main
int main() {
    using namespace std;

    string ex = "1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n";

    std::istringstream r(ex);

    int input_cnt = 0;
    int can_cnt = 0;
    string names[20];
    vector<deque<int>> ballots(20);  
    //voting_readcount(cin, intput_cnt);
    voting_read(r, input_cnt, can_cnt, names, ballots);

    cout << input_cnt << endl;
    cout << can_cnt << endl;
    voting_print(names, can_cnt);
	
	voting_print2d(ballots);
    
    return (0);
}
