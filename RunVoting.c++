
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
#include <iostream> // cin, cout, ios_base
#include "Voting.h"

using namespace std;



int main () {
using namespace std;
ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
voting_solve(cin, cout);
return 0;}