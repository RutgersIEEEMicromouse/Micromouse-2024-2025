#include <iostream>
#include "../include/floodfill.h"
#include"../include/Astar.h"

/**
 * Simple testclient
 */

extern uint16_t floodfill_expand;
int main()
{
    initialize_maze(15,15,true);
    floodfill();
    initialize_maze(1,1,false);
    floodfill();
    fprintf(stderr,"floodfill - nodes expanded: %d\n",floodfill_expand);
    Astar(15,15);
}
