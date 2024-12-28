#include <iostream>
#include "../include/floodfill.h"

/**
 * Simple testclient
 */
int main()
{
    initialize_maze(15,15,true);
    floodfill();
}
