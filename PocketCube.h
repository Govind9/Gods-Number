/*
 * This is header file which include functions and
 * class needed solve 2*2*2 cube with minimum number
 * of moves with maximum 11 moves for any
 * possible configuration
 *
 * author -:
 * Amarjeet Singh Kapoor
 */



#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>


using namespace std;

extern string moves[18];
extern char color[6];


/*
 * This class make object CubeState
 * which define configuration of the given cube
 * and moves away from solved state
 */

class CubeState{
    public:

        char configuration[24];
        vector<short> parent;

        //This is constructure for initializing a cube state
        CubeState();

        // Prints the configuration in which cube is
        void printMe();


};


int cube_solving(CubeState cube);

bool check(CubeState *obj);

CubeState generate_new(CubeState, int);

unsigned long long code_generator(CubeState);

int scramble(CubeState &one);

void give_solution(CubeState);

void test_scope(CubeState);
