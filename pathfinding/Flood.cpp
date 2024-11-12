#include "Flood.h"
#include <iostream>

using namespace std;

// "Definition checked against [extern] declaration"
// maze heuristic
char maze[N][N] = 
{{14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
 {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
 {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},   
 {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},   
 {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},   
 {9,   8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9},   
 {8,   7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8},   
 {7,   6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7},   
 {7,   6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7},   
 {8,   7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8},   
 {9,   8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9},   
 {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},   
 {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},   
 {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},   
 {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},  
 {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14}};

/*
// chebyshev
char maze[N][N] = 
{{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
 {7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7},
 {7, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7},   
 {7, 6, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7},   
 {7, 6, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7},   
 {7, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7},   
 {7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7},  
 {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}};
*/





std::stack<configuration> cellStack;
openCells walls[N][N];
configuration currentCfg;
configuration poppedCfg;

std::stack<configuration> deadendStack;

std::stack<configuration> pathTaken;

void initialize() {
    // set current configuration to (0, 0) facing N
    currentCfg.x = 0;
    currentCfg.y = 0;
    currentCfg.dir = 'N';


#ifdef REAL
    // read from pins, floating voltages are pulled down to GND if 3.3V isn't is applied
    pinMode(memory_button, INPUT_PULLDOWN);
    pinMode(memory_switch, INPUT_PULLDOWN);

    // if switch is on, load the maze from EEPROM
    if(digitalRead(memory_switch)) {
        loadMazeFromEEPROM(maze);
        loadWallsFromEEPROM(walls);
        Serial.println("loaded");
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
#endif


    // start maze from scratch
    // set borders for walls array
    for(int i = 0; i < 16; i++) {
        walls[i][0].openS = false; // move along south wall
        walls[i][15].openN = false; // move along north wall
        walls[0][i].openW = false; // move along west wall
        walls[15][i].openE = false; // move along east wall
	
#ifdef SIM			
	visualizeWalls(i, 0, walls[i][0]);
	visualizeWalls(i, 15, walls[i][15]);
	visualizeWalls(0, i, walls[0][i]);
	visualizeWalls(15, i, walls[15][i]);
#endif


    }

#ifdef REAL
    }
#endif

}

#ifdef REAL
// Maze memory code

void saveMazeToEEPROM(char maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            EEPROM.write(i * N + j, maze[i][j]);
        }
    }
}

void loadMazeFromEEPROM(char maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = EEPROM.read(i * N + j);
        }
    }
}

void saveWallsToEEPROM(openCells walls[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int index = i * N + j + 256;
            EEPROM.write(index, walls[i][j].openN | (walls[i][j].openS << 1) | (walls[i][j].openE << 2) | (walls[i][j].openW << 3));
        }
    }
}

void loadWallsFromEEPROM(openCells walls[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int index = i * N + j + 256;
            unsigned char data = EEPROM.read(index);
            walls[i][j].openN = data & 0x01;
            walls[i][j].openS = (data >> 1) & 0x01;
            walls[i][j].openE = (data >> 2) & 0x01;
            walls[i][j].openW = (data >> 3) & 0x01;
        }
    }
}
#endif








// open cells = no wall, includes cell that we came from
// use sensors/API to check if there's a wall to the front, left, right
// -> make a decision based on current orientation to update walls array
openCells checkOpenCells(configuration currentCfg) {
    openCells temp;
    temp.openN = false;
    temp.openS = false;
    temp.openE = false;
    temp.openW = false;

    int x = currentCfg.x;
    int y = currentCfg.y;
    char dir = currentCfg.dir;


    switch(dir) {
        case 'N':
            temp.openS = true;
            if(!API::wallFront()) temp.openN = true;
            if(!API::wallLeft()) temp.openW = true;
            if(!API::wallRight()) temp.openE = true;
            break;
        case 'S':
            temp.openN = true;
            if(!API::wallFront()) temp.openS = true;
            if(!API::wallLeft()) temp.openE = true;
            if(!API::wallRight()) temp.openW = true;
            break;
        case 'E':
            temp.openW = true;
            if(!API::wallFront()) temp.openE = true;
            if(!API::wallLeft()) temp.openN = true;
            if(!API::wallRight()) temp.openS = true;
            break;
        case 'W':
            temp.openE = true;
            if(!API::wallFront()) temp.openW = true;
            if(!API::wallLeft()) temp.openS = true;
            if(!API::wallRight()) temp.openN = true;
            break;
    }


    //update walls array
    walls[x][y].openN = temp.openN;
    walls[x][y].openS = temp.openS;
    walls[x][y].openE = temp.openE;
    walls[x][y].openW = temp.openW;

    //update for adjacent cells too
    //N = +y
    //S = -y
    //E = +x
    //W = -x	
    if(y+1 <= 15 && temp.openN) walls[x][y+1].openS = temp.openN; // update openS of north cell 
    if(y-1 >= 0 && temp.openS) walls[x][y-1].openN = temp.openS; // update south cell
    if(x+1 <= 15 && temp.openE) walls[x+1][y].openW = temp.openE; // update openW of east cell
    if(x-1 >= 0 && temp.openW) walls[x-1][y].openE = temp.openW; // update west cell



#ifdef SIM
    visualizeWalls(x, y, walls[x][y]);
#endif

    return temp;
}



void flowElevation() {
    // given the maze, configuration, and wall checks, move to lower elevation until we hit 0
    // prioritize movements without turns if possible (DONE)
    // prioritize movements to unvisited first

    //    Serial.println("Begin flow");
    int x = currentCfg.x; // up and down on the array = EW, first term
    int y = currentCfg.y; // left and right on the array = NS, second term
	
    walls[x][y].visited = true;

    // check if surrounding cells are valid, 
    // pick the lowest out of the open cells,
    // and move forward
    openCells checkOpen = checkOpenCells(currentCfg);
    bool openN = checkOpen.openN;
    bool openS = checkOpen.openS;
    bool openE = checkOpen.openE;
    bool openW = checkOpen.openW;

    //min of the open cells
    int N = 1337;
    int S = 1337;
    int E = 1337;
    int W = 1337;

    //N = +y
    //S = -y
    //E = +x
    //W = -x

    if(y+1 <= 15 && openN) N = maze[x][y+1];
    if(y-1 >= 0 && openS) S = maze[x][y-1];
    if(x+1 <= 15 && openE) E = maze[x+1][y];
    if(x-1 >= 0 && openW) W = maze[x-1][y];

    // find the min using arraysort
    int arraySort[4] = {N, S, E, W};
    std::sort(arraySort, arraySort + 4);
    int min = arraySort[0];
    // std::cerr << "Min Cell Calculated: " << min << std::endl;
    
    // move to minimum of open cells (usually presentCellValue - 1)

    bool Nvisited = walls[x][y+1].visited;
    bool Svisited = walls[x][y-1].visited;
    bool Evisited = walls[x+1][y].visited;
    bool Wvisited = walls[x-1][y].visited;



    // prefer to move forward without spinning
    char facing = currentCfg.dir;

    //std::cerr << facing << std::endl;
    switch(facing) {

        case 'N':
	    if(N == min && maze[x][y] == min + 1 && openN && !Nvisited) {
		move('N');
		return;
	    }
	    break;
        case 'S':
	    if(S == min && maze[x][y] == min + 1 && openS && !Svisited) {
		move('S');
		return;
	    }
	    break;

        case 'E':
	    if(E == min && maze[x][y] == min + 1 && openE && !Evisited) {
		move('E');
		return;
	    }
	    break;

        case 'W':
	    if(W == min && maze[x][y] == min + 1 && openW && !Wvisited) {
		move('W');
		return;
	    }
            break;
    }


    // std::cerr << "backup" << std::endl;
    // extra parameters for move
    // don't move to higher elevations ever, wait for cell update before moving 
    if(N == min && maze[x][y] == min + 1 && openN && !Nvisited) {
        move('N');
        return;
    }
    if(S == min && maze[x][y] == min + 1 && openS && !Svisited) {
        move('S');
        return;
    }
    if(E == min && maze[x][y] == min + 1 && openE && !Evisited) {
        move('E');
        return;
    }
    if(W == min && maze[x][y] == min + 1 && openW && !Wvisited) {
        move('W');
        return;
    }

    // backup backup 2
    if(N == min && maze[x][y] == min + 1 && openN) {
        move('N');
        return;
    }
    if(S == min && maze[x][y] == min + 1 && openS) {
        move('S');
        return;
    }
    if(E == min && maze[x][y] == min + 1 && openE) {
        move('E');
        return;
    }
    if(W == min && maze[x][y] == min + 1 && openW) {
        move('W');
        return;
    }


    return;
}



// if minimum distance of neighboring OPEN cells is not presentCellValue - 1
// ->  replace present cell's distance with minimum + 1
// -> push all neighbor locations onto the stack except the goal locations 
//    (since these should stay 0)
void checkNeigboringOpen(configuration poppedCfg) {
    
    // For the popped configuration, refer to the global 
    // walls array instead of checking from the API

    int x = poppedCfg.x;
    int y = poppedCfg.y;
    // char dir = poppedCfg.dir;

    bool openN = walls[x][y].openN;
    bool openS = walls[x][y].openS;
    bool openE = walls[x][y].openE;
    bool openW = walls[x][y].openW;

    //min of the open cells
    int N = 1337;
    int S = 1337;
    int E = 1337;
    int W = 1337;

    //N = +y
    //S = -y
    //E = +x
    //W = -x

    if(y+1 <= 15 && openN) N = maze[x][y+1];
    if(y-1 >= 0 && openS) S = maze[x][y-1];
    if(x+1 <= 15 && openE) E = maze[x+1][y];
    if(x-1 >= 0 && openW) W = maze[x-1][y];


    // find the min using arraysort
    int arraySort[4] = {N, S, E, W};
    std::sort(arraySort, arraySort + 4);
    int min = arraySort[0];
    // std::cerr << maze[x][y] << std::endl;
    // std::cerr << arraySort[0] << " " <<  arraySort[1] << " " << arraySort[2] << " " <<arraySort[3] << std::endl;

    // if minimum distance of neighboring open cells is not presentCellValue - 1

    if(min != maze[x][y] - 1) {
        // std::cerr << "min check failed";
        // replace present cell's distance with minimum + 1
            maze[x][y] = min + 1;

        // push all neighbor locations onto the stack except the goal locations

        configuration pushCfg = poppedCfg;


        if(x+1 <= 15 && !((x+1==7 && y==7) || (x+1==7 && y==8) || (x+1==8 && y==7) || (x+1==8 && y==8))) {
            pushCfg.x += 1;
            cellStack.push(pushCfg);
            // std::cerr << "Pushed (" << pushCfg.x << ", " << pushCfg.y << ")";
            pushCfg.x -= 1;
        }
        if(x-1 >= 0 && !((x-1==7 && y==7) || (x-1==7 && y==8) || (x-1==8 && y==7) || (x-1==8 && y==8))) {
            pushCfg.x -= 1;
            cellStack.push(pushCfg);
            // std::cerr << "Pushed (" << pushCfg.x << ", " << pushCfg.y << ")";
            pushCfg.x += 1;
        }
        if(y+1 <= 15 && !((x==7 && y+1==7) || (x==7 && y+1==8) || (x==8 && y+1==7) || (x==8 && y+1==8))) {
            pushCfg.y += 1;
            cellStack.push(pushCfg);
            // std::cerr << "Pushed (" << pushCfg.x << ", " << pushCfg.y << ")";
            pushCfg.y -= 1;
        }
        if(y-1 >= 0 && !((x==7 && y-1==7) || (x==7 && y-1==8) || (x==8 && y-1==7) || (x==8 && y-1==8))) {
            pushCfg.y -= 1;
            cellStack.push(pushCfg);
            // std::cerr << "Pushed (" << pushCfg.x << ", " << pushCfg.y << ")";
            pushCfg.y += 1;
        }
    }
	




    // std::cerr << "stack size: " << cellStack.size();
	

#ifdef SIM
    visualizeMaze(maze);
#endif

    return;
}



/*
    // check for walls to the front, right, or left
    static bool wallFront();
    static bool wallRight();
    static bool wallLeft();

    //allow the mouse to move
    static void moveForward(int distance = 1);
    static void turnRight();
    static void turnLeft();

    //sample calls
    API::wallLeft();
    API:turnLeft();
*/
void move(char direction) {
    
    char facing = currentCfg.dir;
    
    // if facing and direction are the same, go straight
    if(facing == direction) {
        API::moveForward();
    } else {

        if(facing == 'N') {
            switch(direction) {

            case 'S': // turn around
            API::turnLeft(); API::turnLeft(); API::moveForward();
            break;

            case 'W': // turnLeft
            API::turnLeft(); API::moveForward();
            break;

            case 'E': // turnRight
            API::turnRight(); API::moveForward();
            break;
            }
        }

        if(facing == 'S') {
            switch(direction) {

            case 'N': // turn around
            API::turnLeft(); API::turnLeft(); API::moveForward();
            break;

            case 'E': // turnLeft
            API::turnLeft(); API::moveForward();
            break;

            case 'W': // turnRight
            API::turnRight(); API::moveForward();
            break;
            }
        }

        if(facing == 'E') {
            switch(direction) {

            case 'W': // turn around
            API::turnLeft(); API::turnLeft(); API::moveForward();
            break;

            case 'N': // turnLeft
            API::turnLeft(); API::moveForward();
            break;

            case 'S': // turnRight
            API::turnRight(); API::moveForward();
            break;
            }
        }

        if(facing == 'W') {
            switch(direction) {

            case 'E': // turn around
            API::turnLeft(); API::turnLeft(); API::moveForward();
            break;

            case 'S': // turnLeft
            API::turnLeft(); API::moveForward();
            break;

            case 'N': // turnRight
            API::turnRight(); API::moveForward();
            break;
            }
        }
    }
    
    //N = +y
    //S = -y
    //E = +x
    //W = -x

    currentCfg.dir = direction;

    switch(direction) {

        case 'N':
            currentCfg.y++;
        break;

        case 'S':
            currentCfg.y--;
        break;

        case 'E':
            currentCfg.x++;
        break;

        case 'W':
            currentCfg.x--;
        break;
    }


    return;
}

/*
void invertMaze(char goal) {
    std::cerr << "HELLO????";

    int endCell;
    // if the goal is to go back to the start
    if(goal == 's') {
        endCell = maze[0][0];
    }
    // if the goal is to get back to the center
    else if(goal == 'c') {
        // use minimum of the 4 center squares as the endCell
	int arraySort[4] = {maze[7][7], maze[7][8], maze[8][7], maze[8][8]};
	std::sort(arraySort, arraySort + 4);
	endCell = arraySort[0];
	}

// deadend filler, if cell has value greater than value of the startpoint
// set the cell as a closed cell with openN, openS, openE, openW = false

// also if a cell next to a dead end cell only has 1 other open cell
// it is a closed cell as well 
std::stack<configuration> deadendStack;
configuration pushCfg;

for(int i = 0; i < 16; i++) {
for(int j = 0; j < 16; j++) {
if(maze[i][j] > goal) {
pushCfg.x = i;
pushCfg.y = j;
// don't need dir
deadendStack.push(pushCfg);
}
}
}

//N = +y
//S = -y
//E = +x
//W = -x

while(!deadendStack.empty()) {
poppedCfg = deadendStack.top();
deadendStack.pop();

int x = poppedCfg.x;
int y = poppedCfg.y;
// don't need dir

// first push open neigbors to stack
openCells neigboringOpen;
neigboringOpen.openN = walls[x][y].openN;
neigboringOpen.openS = walls[x][y].openS;
neigboringOpen.openE = walls[x][y].openE;
neigboringOpen.openW = walls[x][y].openW;

pushCfg = poppedCfg;
if(neigboringOpen.openN) {
pushCfg.y++; 
deadendStack.push(pushCfg);
pushCfg.y--;
}
if(neigboringOpen.openS) {
pushCfg.y--; 
deadendStack.push(pushCfg);
pushCfg.y++;
}
if(neigboringOpen.openE) {
pushCfg.x++; 
deadendStack.push(pushCfg);
pushCfg.x--;
}
if(neigboringOpen.openW) {
	pushCfg.x--; 
	deadendStack.push(pushCfg);
	pushCfg.x++;
}

// conditions for being a deadend cell:
// - value greater than start node (we already did this)
// - is closed off on 3 sides
// - is next to a deadend cell (adding to stack sorts these) and only has 2 open side
//   (one side that leads into the dead end and one that leads out)
int numOpen = neigboringOpen.openN + neigboringOpen.openS + neigboringOpen.openE + neigboringOpen.openW;
if((maze[x][y] > goal) || (numOpen <= 2)) {
	walls[x][y].openN = false;
	walls[x][y].openS = false;
	walls[x][y].openE = false;
	walls[x][y].openW = false;
}
}

//invert the maze by doing endCell - maze[i][j]
// -> endCell will become 0 (goal)
for(int i = 0; i < 16; i++) {
	for(int j = 0; j < 16; j++) {
		maze[i][j] = endCell - maze[i][j];
	}
}

return;
}
*/

#ifdef SIM
// printout maze with bot starting at bottom left
void mazePrintout() {
	// printout maze
	std::cerr << std::endl;
	for(int j = 15; j >= 0; j--) {
		for(int i = 0; i < 16; i++) {

			if(currentCfg.x == i && currentCfg.y == j) {
				if(maze[i][j] < 10) std::cerr << "[" << static_cast<int>(maze[i][j]) << "], ";
				else std::cerr << "[" << static_cast<int>(maze[i][j]) << "], ";
			} else {
				if(maze[i][j] < 10) std::cerr << " " << static_cast<int>(maze[i][j]) << ", ";
				else std::cerr << static_cast<int>(maze[i][j]) << ", ";
			}


		}
		std::cerr << std::endl;

	}
	std::cerr << std::endl;        
}

// update visualizations in sim
void visualizeMaze(char maze[N][N]) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			API::setText(i, j, to_string(static_cast<int>(maze[i][j])));
		}
	}
}


void visualizeWalls(int i, int j, openCells cell) {
	if (!walls[i][j].openN) API::setWall(i, j, 'n');
	if (!walls[i][j].openS) API::setWall(i, j, 's');
	if (!walls[i][j].openE) API::setWall(i, j, 'e');
	if (!walls[i][j].openW) API::setWall(i, j, 'w');
}

#endif

#ifdef REAL
void mazePrintout() {
	// printout maze
	for(int j = 4; j >= 0; j--) {
		for(int i = 0; i < 5; i++) {

			if(currentCfg.x == i && currentCfg.y == j) {
				Serial.print("[");
				Serial.print(maze[i][j]);
				Serial.print("], ");
			} else {
				Serial.print(" ");
				Serial.print(maze[i][j]);
				Serial.print(", ");
			}


		}
		Serial.println();
	}
	Serial.println();
}
#endif




void runMaze(char goal) {
	//Serial.print("Start 2");

	int loopCondition = 1;

	while(loopCondition) {

		pathTaken.push(currentCfg);
#ifdef SIM
		API::setColor(currentCfg.x, currentCfg.y, 'a');
#endif



		// Micromouse moves from higher to lower elevations
		// std::cerr << "[" << currentCfg.x << " " << currentCfg.y << " " << currentCfg.dir << "] -> " << maze[currentCfg.x][currentCfg.y] << std::endl;
		flowElevation();
		//end condition
		if(goal == 'c') {
			if((currentCfg.x == 7 || currentCfg.x == 8) && (currentCfg.y == 7 || currentCfg.y == 8)) {
				// set cell as visited
				walls[currentCfg.x][currentCfg.y].visited = true;

				// update walls in center rq
				openCells checkOpen = checkOpenCells(currentCfg);

				// close off other entrances to the maze
				//  ___ ___
				// |7,8 8,8|
				// |       |
				// |7,7 8,7|
				// |___ ___|


				if (!(currentCfg.x == 7 && currentCfg.y == 7)) {			
					walls[7][6].openN = false;
					walls[7][7].openS = false; // 7,7
					walls[6][7].openE = false;
					walls[7][7].openW = false; // 7,7
				}


				if (!(currentCfg.x == 7 && currentCfg.y == 8)) {			

					walls[7][8].openN = false; // 7,8
					walls[7][9].openS = false;
					walls[6][8].openE = false;
					walls[7][8].openW = false; // 7,8
				}

				if (!(currentCfg.x == 8 && currentCfg.y == 7)) {			
					walls[8][6].openN = false;
					walls[8][7].openS = false; // 8,7
					walls[8][7].openE = false; // 8,7
					walls[9][7].openW = false;
				}

				if (!(currentCfg.x == 8 && currentCfg.y == 8)) {
					walls[8][8].openN = false; // 8,8
					walls[8][9].openS = false;
					walls[8][8].openE = false; // 8,8
					walls[9][8].openW = false;
				}		


#ifdef SIM			
				for (int i = 7; i <= 8; i++) {
					for (int j = 7; j <= 8; j++) {
						visualizeWalls(i, j, walls[i][j]);
					}
				}
#endif

				loopCondition = 0;
			}
		}


		// std::cerr << "Walls Array "<< walls[currentCfg.x][currentCfg.y].openN << walls[currentCfg.x][currentCfg.y].openS << walls[currentCfg.x][currentCfg.y].openE << walls[currentCfg.x][currentCfg.y].openW << std::endl;

		//1) Push the current cell location onto the stack
		cellStack.push(currentCfg);

		//2) Repeat while stack is not empty        
		while(!cellStack.empty()) {
			//pull the cell location from the stack
			poppedCfg = cellStack.top();
			cellStack.pop();

			// std::cerr << poppedCfg.x << " " << poppedCfg.y << " " << poppedCfg.dir << std::endl;

			checkNeigboringOpen(poppedCfg);
		}

		//mazePrintout();

	}

#ifdef REAL
	// wait for button push for storing maze info into EEPROM
	while(1) {
		delay(300);
		if(digitalRead(memory_button)) {
			saveMazeToEEPROM(maze);
			saveWallsToEEPROM(walls);
			Serial.println("saved");
			digitalWrite(LED_BUILTIN, LOW);
			delay(200);
			digitalWrite(LED_BUILTIN, HIGH);
			delay(200);
			digitalWrite(LED_BUILTIN, LOW);
			delay(200);
			digitalWrite(LED_BUILTIN, HIGH);
		}

	}

#endif

}

//N = +y
//S = -y
//E = +x
//W = -x

void backTrack() {
	while(!pathTaken.empty()) {
		int x = pathTaken.top().x;
		int y = pathTaken.top().y;
		pathTaken.pop();

		int xDiff = x - currentCfg.x;
		int yDiff = y - currentCfg.y;

		if(yDiff == 1) {
			move('N');
		}
		if(yDiff == -1) {
			move('S');
		}
		if(xDiff == 1) {
			move('E');
		}
		if(xDiff == -1) {
			move('W');
		}
	}
}

// TODO
// Idea?
// Break maze into 33x33, 16 cells + 15 inbetween cells, also + 2 inbetween cells for the walls
// Move from each half cell to half cell using Chebyshev distance
// Refactor move to include cardinal combinations
void speedrun() {
	bool highResMaze[33][33] = {}; // 33x33 array initialized to false, true represents obstacle
	// (15,15) is the middle of the bottom left square
	// (17,17) is the middle of the top right square

	for(int i = 0; i < 33; i++) {
		highResMaze[i][0] = true; // move along south wall
		highResMaze[i][32] = true; // move along north wall
		highResMaze[0][i] = true; // move along west wall
		highResMaze[32][i] = true; // move along east wall
	}

	// populate the high res maze from existing walls array
	// -> the cell at (0,0) is (1,1) in highResMaze
	// x = 2i+1, y = 2j + 1

	// -> the wall to the north of (0, 0) would be (1, 2)
	// -> also set the ones to the left and right (0, 2) and (2, 2)

	//N = +y
	//S = -y
	//E = +x
	//W = -x

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			int highResX = 2*i+1;
			int highResY = 2*j+1;

			openCells cell = walls[i][j];
			if(!cell.openN) {
				highResMaze[highResX][highResY + 1] = true; // straight north
				highResMaze[highResX-1][highResY + 1] = true; highResMaze[highResX+1][highResY + 1] = true; // adjacent diagonals
			}
			if(!cell.openS) {
				highResMaze[highResX][highResY - 1] = true;
				highResMaze[highResX-1][highResY - 1] = true; highResMaze[highResX+1][highResY - 1] = true;
			}
			if(!cell.openE) {
				highResMaze[highResX + 1][highResY] = true;
				highResMaze[highResX + 1][highResY-1] = true; highResMaze[highResX + 1][highResY+1] = true;
			}
			if(!cell.openW) {
				highResMaze[highResX - 1][highResY] = true;
				highResMaze[highResX - 1][highResY-1] = true; highResMaze[highResX - 1][highResY+1] = true;
			}

			// temporary measure to not attempt to solve with unvisited cells
			if(!cell.visited) {
				highResMaze[highResX-1][highResY-1] = true; highResMaze[highResX][highResY-1] = true; highResMaze[highResX+1][highResY-1] = true;
				highResMaze[highResX-1][highResY] = true; highResMaze[highResX][highResY] = true; highResMaze[highResX+1][highResY] = true;
				highResMaze[highResX-1][highResY+1] = true; highResMaze[highResX][highResY+1] = true; highResMaze[highResX+1][highResY+1] = true;
			}

		}
	}


	for(int j = 32; j >= 0; j--) {
		for(int i = 0; i < 33; i++) {
			std::cerr << highResMaze[i][j] << " ";
		}
		std::cerr << std::endl;
	}


	// straight line A*
	Node highResMazeNode[33][33];

	// update nodes, don't need to do outer walls
	for (int i = 1; i < 33-1; i++) {
		for (int j = 1; j < 33-1; j++) {
			highResMazeNode[i][j].X = i;
			highResMazeNode[i][j].Y = j;
			highResMazeNode[i][j].hCost = calculateH(i, j);
		}
	}
	
	// (start point "comes from" the node behind it)
	highResMazeNode[1][1].parentX = 1;
	highResMazeNode[1][1].parentX = 0;

	//N = +y
	//S = -y
	//E = +x
	//W = -x


	// Possible movements: cardinal and diagonal
	std::vector<std::pair<int, int>> directions = {
		{ 0,  1},  // Up
		{ 0, -1},  // Down
		{-1,  0},  // Left
		{ 1,  0},  // Right
		{-1,  1},  // Top-left
		{ 1,  1},  // Top-right
		{-1, -1},  // Bottom-left
		{ 1, -1}   // Bottom-right
	};


	// initialize A* datatypes

	// Min-heap priority queue using Node's overloaded operator>
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
	// set to check if node is in open set, since checking in min heap is inefficient
	std::set<std::pair<int, int>> openSetCoords;


	// set f and g costs for start 
	highResMazeNode[1][1].gCost = 0;
	highResMazeNode[1][1].fCost = highResMazeNode[1][1].gCost + highResMazeNode[1][1].hCost; 


	// start adding and removing stuff from open set and repeat

	// add start node to open set
	openSet.push(highResMazeNode[1][1]);
	openSetCoords.insert({1, 1});
	

	while(!openSet.empty()) {
		Node current = openSet.top();

		// std::cerr << "(" << current.X << ", " << current.Y << ") ";

		openSet.pop();
		openSetCoords.erase({current.X, current.Y});
		
		// reconstruct path if current is in center
		if((current.X >= 15 && current.X <= 17) && (current.Y >= 15 && current.Y <= 17)) {
			std::cerr << "reconstruct path" << std::endl;

			// essentially a dynamic array with <int, int> datatype
			std::vector<std::pair<int, int>> path;
			
			while (!(current.X == 1 && current.Y == 1)) {
				// adds backtracked node to end of list
				path.push_back({current.X, current.Y});
				current = highResMazeNode[current.parentX][current.parentY];

			}
			
			// add beginning node
			path.push_back({1, 1});

			// add direction node for start
			path.push_back({1, 0});

			
			// reverse list to start from beginning
			std::reverse(path.begin(), path.end());
			
			// Print the path
			std::cerr << "Path: ";
			for (const auto& coord : path) {
				std::cerr << "(" << coord.first << ", " << coord.second << ") " << std::endl;
			}
			std::cerr << std::endl;
					
	

			// convert path to straights and turns
			std::vector<std::pair<char, uint8_t>> commands;
			
			// Dictionary (map) of directions to angles
			std::map<std::pair<int, int>, double> directionAngles = {
				{{ 0,  1}, 0.0},      // Up
				{{ 0, -1}, 180.0},    // Down
				{{-1,  0}, 270.0},    // Left
				{{ 1,  0}, 90.0},     // Right
				{{-1,  1}, 315.0},    // Top-left
				{{ 1,  1}, 45.0},     // Top-right
				{{-1, -1}, 225.0},    // Bottom-left
				{{ 1, -1}, 135.0}     // Bottom-right
			};

			
			// command to go from (1,1) to 			
			// Iterate with index and item
			
			// start at index 2, since index 0 is (1,0) and index 1 is (1,1)
			for (std::size_t i = 2; i < path.size(); ++i) {
				
				std::pair<int, int> nextNode = {path[i].first, path[i].second};
				std::pair<int, int> nextNodeDirection = {path[i].first - path[i-1].first, path[i].second - path[i-1].second};
				

				std::pair<int, int> currNode = {path[i-1].first, path[i-1].second};
				std::pair<int, int> currNodeDirection = {path[i-1].first - path[i-2].first, path[i-1].second - path[i-2].second};
				
				// if nextNode heads in the same direction, go forward
				if (nextNodeDirection.first == currNodeDirection.first && nextNodeDirection.second == currNodeDirection.second) {
							
					// if current command is to go straight and previous command is to go straight, combine them
					if (!commands.empty() && commands.back().first == 'F') {
						commands.back().second += 1;
					} else {
					// for case at beginning where it's same direction but no straight command, append it
						commands.push_back({'F', 1});
					}

				} else {
					// make a turn and then move
					// desired field angle, use dictionary instead of atan2 for precision 
					double nextNodeDirectionAngle = directionAngles[nextNodeDirection];
					
					// can't do absolute orientation on SIM, converts to left/right and left/right45
#ifdef SIM
					double currNodeDirectionAngle = directionAngles[currNodeDirection];
					
					// Calculate the raw angle difference
					double desiredAngle = nextNodeDirectionAngle;
					double currentAngle = currNodeDirectionAngle;	

					double angleDiff = desiredAngle - currentAngle;

					std::cerr << currentAngle << ", " << desiredAngle << std::endl;
					
					// Normalize the angle difference to be within [-180°, 180°]
					if (angleDiff > 180.0) { angleDiff -= 360.0;
					} else if (angleDiff < -180.0) { angleDiff += 360.0; }
						
					// allow for some floating point inaccuracy
					while(abs(angleDiff) > 1) {

						uint8_t turnAmount = 45;
						if (abs(angleDiff) > 45) {
							turnAmount = 90;	
						}

						if(angleDiff > 0) {
							// turn right
							angleDiff -= static_cast<double>(turnAmount);
							commands.push_back({'R', turnAmount});
						} else if (angleDiff < 0) {
							// turn left
							angleDiff += static_cast<double>(turnAmount);
							commands.push_back({'L', turnAmount});
						}
					}
					
					// finally move forward
					commands.push_back({'F', 1});
#endif
				}
			}
		
			
			// execute the actions in commands
#ifdef SIM
			// turn the bot to face north
			API::turnLeft();
			API::turnLeft();

#endif

			std::cerr << "speedrun" << std::endl;

			// Range-based for loop
			for (const auto& command : commands) {
				std::cerr << "Action: " << command.first << ", Amount: " << static_cast<double>(command.second) << std::endl;
				
				switch(command.first) {
	
					case 'F':
						API::moveForwardHalf(static_cast<int>(command.second));

						break;
					case 'L':
						if (command.second == 45) { API::turnLeft45();
						} else if (command.second == 90) { API::turnLeft(); }
						break;
					case 'R':
						if (command.second == 45) { API::turnRight45();
						} else if (command.second == 90) { API::turnRight(); }
						break;
					default:
						std::cerr << "no caseoh" << std::endl;
				}		
			}
				

			std::cerr << "Done" << std::endl;
			return;
	    	}


		
		// add neighbors of current to open set
		// Iterate over movements
	        for (const auto& direction : directions) {
	            int newX = current.X + direction.first;
	            int newY = current.Y + direction.second;

		    // if obstacle, continue
		    if(highResMaze[newX][newY]) continue;

		    // increase cost if there is a direction change
		    int currentNodeDirectionX = highResMazeNode[current.X][current.Y].X - highResMazeNode[current.X][current.Y].parentX;  
		    int currentNodeDirectionY = highResMazeNode[current.X][current.Y].X - highResMazeNode[current.X][current.Y].parentY; 
		    
		    bool sameDirection = (currentNodeDirectionX == direction.first) && (currentNodeDirectionY == direction.second);
		    
		    
		    float tentative_gCost = highResMazeNode[current.X][current.Y].gCost;

		    if(!sameDirection) {
			tentative_gCost += 1;
		    }
		    
		    // if path to neighbor is better than stored, update it
		    if (tentative_gCost < highResMazeNode[newX][newY].gCost) {
			highResMazeNode[newX][newY].parentX = current.X;
			highResMazeNode[newX][newY].parentY = current.Y;
			
			highResMazeNode[newX][newY].gCost = tentative_gCost;
			highResMazeNode[newX][newY].fCost = tentative_gCost + calculateH(newX, newY);
			
			// .find returns .end() if it's not in open set
			// if not in open set, add it to openSet
			if (openSetCoords.find({newX, newY}) == openSetCoords.end()) {
				openSet.push(highResMazeNode[newX][newY]);
				openSetCoords.insert({newX, newY});
			}
		    }
		}
	}
	std::cerr << "failure" << std::endl;
	return;

}


