#include <iostream>
#include "../include/floodfill.h"
#include"../include/Astar.h"
/**
 * Simple testclient
 */
int main()
{
    initialize_maze(15,15,true);
    floodfill();
    initialize_maze(1,1,false);
    floodfill();
    Astar(15,15);
}
