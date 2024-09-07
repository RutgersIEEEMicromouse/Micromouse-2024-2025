#ifndef FLOOD_H
#define FLOOD_H
#pragma once


#include "API.h"
//#include "..\Motors.h"
#include<stack>
#include<algorithm>


//// variable declarations
const int N = 16; 

// global array for the maze, tells the robot how to move
extern char maze[N][N];


struct configuration {
    int x;
    int y;
    char dir;
};

// How to make a global variable
// https://edisciplinas.usp.br/pluginfile.php/5453726/mod_resource/content/0/Extern%20Global%20Variable.pdf

// How to use the stl stack
// https://cplusplus.com/reference/stack/stack/
extern std::stack<configuration> cellStack;
extern configuration currentCfg; // global struct for keeping track of current pos/orientation
extern configuration poppedCfg; // global struct for popped cell cause why not

extern std::stack<configuration> pathTaken;

// uses bitfields to specify each bool to only look at 1 bit
// instead of 4 bytes/cell
struct openCells {
    bool openN : 1; 
    bool openS : 1;
    bool openE : 1;
    bool openW : 1;
    // Constructor that initializes each variable to be open (1)
    openCells() : openN(1), openS(1), openE(1), openW(1) {}
};
// list of walls for recursive cell update to use
extern openCells walls[N][N];



//// function declarations
void initialize();
void flowElevation();
openCells checkOpenCells(configuration currentCfg);
void checkNeigboringOpen(configuration poppedCfg);
void move(char direction);
void invertMaze(char goal);
void mazePrintout();
void runMaze(char goal);
void backTrack();

#endif
