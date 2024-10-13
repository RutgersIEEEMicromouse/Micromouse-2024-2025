#include <iostream>
#include "../include/floodfill.h"

/**
 * Simple testclient
 */
int main()
{
    initialize_maze({7,7},true);
    floodfill();
    movebot();
    
}
