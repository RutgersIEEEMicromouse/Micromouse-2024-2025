#include "API.h"

#ifdef SIM




#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

#include "Flood.h"
using namespace std;


// Flood fill algorithm
// mouse tries to approach smaller values of the maze
// as the mouse explores, it updates the values along its path. 
void log(const std::string& text) {
    std::cerr << text << std::endl;
}

int main(int argc, char* argv[]) {
    log("Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");

    //Modified Flood Fill
    //https://marsuniversity.github.io/ece387/FloodFill.pdf

    log(to_string(sizeof(maze)));
    log(to_string(sizeof(walls)));
    //// STEP 1: Initial Solve
    initialize();
    runMaze('c');
    backTrack();

    for (int run = 0; run < 10; run++) {
	    runMaze('c');
	    backTrack();
    }
    //speedrun();
}

#endif
