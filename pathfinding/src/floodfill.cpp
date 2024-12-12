#include "../include/floodfill.h"
#include "../include/API.h"
#include<queue>
#include<cstdio>


cell maze[33][33]; // Center is 14, 14

static bool hasnorthwall(point p) {
    if (p.y == 32) {
        return true; // Edge of the maze, treat as a wall.
    }
    return maze[p.x][p.y + 1].weight == -2;
}

static bool hassouthwall(point p) {
    if (p.y == 0) {
        return true; // Edge of the maze, treat as a wall.
    }
    return maze[p.x][p.y - 1].weight == -2;
}

static bool haseastwall(point p) {
    if (p.x == 32) {
        return true; // Edge of the maze, treat as a wall.
    }
    return maze[p.x + 1][p.y].weight == -2;
}

static bool haswestwall(point p) {
    if (p.x == 0) {
        return true; // Edge of the maze, treat as a wall.
    }
    return maze[p.x - 1][p.y].weight == -2;
}

void initialize_maze(uint8_t x, uint8_t y, bool reset) {
    point dest = {x, y};
    std::queue<point> myqueue;

    if (reset) {
        for (int i = 0; i < 33; i++) {
            for (int j = 0; j < 33; j++) {
                maze[i][j].weight = -1;
            }
        }
    }

    myqueue.push(dest);
    maze[dest.x][dest.y].weight = 0.0f;

    while (!myqueue.empty()) {
        point temp = myqueue.front();
        myqueue.pop();

        // Look at neighbors
        if (!hasnorthwall(temp) && maze[temp.x][temp.y + 1].weight == -1) {
            maze[temp.x][temp.y + 1].weight = maze[temp.x][temp.y].weight + 0.5f;
            myqueue.push({temp.x, static_cast<uint8_t>(temp.y + 1)});
        }
        if (!hassouthwall(temp) && maze[temp.x][temp.y - 1].weight == -1) {
            maze[temp.x][temp.y - 1].weight = maze[temp.x][temp.y].weight + 0.5f;
            myqueue.push({temp.x, static_cast<uint8_t>(temp.y - 1)});
        }
        if (!haseastwall(temp) && maze[temp.x + 1][temp.y].weight == -1) {
            maze[temp.x + 1][temp.y].weight = maze[temp.x][temp.y].weight + 0.5f;
            myqueue.push({static_cast<uint8_t>(temp.x + 1), temp.y});
        }
        if (!haswestwall(temp) && maze[temp.x - 1][temp.y].weight == -1) {
            maze[temp.x - 1][temp.y].weight = maze[temp.x][temp.y].weight + 0.5f;
            myqueue.push({static_cast<uint8_t>(temp.x - 1), temp.y});
        }
    }

    // Print the maze weights
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 33; j++) {
            printf("%.2f  ", maze[i][j].weight);
        }
        printf("\n");
    }
}

void floodfill(){
    
}

void reflood(){

}