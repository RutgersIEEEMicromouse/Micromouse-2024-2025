#include "../include/floodfill.h"
#include "../include/API.h"
#include <stack>
#include <queue>
#include <cstdio>
#include <iostream>

static cell maze[16][16]; ///< 2D array representing the maze
static point destination, current; ///< Current and destination points
static char direction; ///< Current direction of the bot

/**
 * @brief Reflood the maze to reset weights for flood filling.
 * @param curr Current point to start reflooding.
 */
static void reflood();

/**
 * @brief Initializes the maze and performs BFS to set weights.
 * @param dest Destination point for the BFS.
 * @param reset Boolean indicating if the maze should be reset.
 */
void initialize_maze(point dest, bool reset)
{
    if (reset)
    {
        // Reset maze cells
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                maze[i][j].raw = 0; // Clear raw data
                maze[i][j].weight = -1; // Set initial weights to -1
            }
        }
        
        // Set walls around the maze
        for (int i = 0; i < 16; i++)
        {
            maze[i][0].S = 1; // South wall
            API::setWall(i, 0, 's');
            maze[i][15].N = 1; // North wall
            API::setWall(i, 15, 'n');
            maze[0][i].W = 1; // West wall
            API::setWall(0, i, 'w');
            maze[15][i].E = 1; // East wall
            API::setWall(15, i, 'e');
        }
        current.x = 0; // Starting point
        current.y = 0;
        direction = 'n'; // Initial direction
    }

    destination = dest; // Set destination
    std::queue<point> BFS; // Queue for BFS
    BFS.push(destination); // Push destination onto queue
    API::setText(destination.x, destination.y, "0"); // Set text for destination
    maze[destination.x][destination.y].weight = 0; // Set weight of destination

    // BFS to set weights
    while (!BFS.empty())
    {
        point temp = BFS.front(); // Get front point
        BFS.pop();
        int16_t tempweight = maze[temp.x][temp.y].weight; // Current weight
        char buf[10]; // Buffer for text

        // Look at neighbors with boundary checks
        if (temp.y + 1 < 16 && !maze[temp.x][temp.y].N && maze[temp.x][temp.y + 1].weight == -1)
        {
            maze[temp.x][temp.y + 1].weight = tempweight + 1; // Update weight
            sprintf(buf, "%d", tempweight + 1); // Convert weight to string
            API::setText(temp.x, temp.y + 1, buf); // Set text for neighbor
            uint8_t y = temp.y + 1;
            BFS.push({temp.x, y}); // Push neighbor onto queue
        }
        if (temp.x + 1 < 16 && !maze[temp.x][temp.y].E && maze[temp.x + 1][temp.y].weight == -1)
        {
            maze[temp.x + 1][temp.y].weight = tempweight + 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x + 1, temp.y, buf);
            uint8_t x = temp.x + 1;
            BFS.push({x, temp.y});
        }
        if (temp.y - 1 >= 0 && !maze[temp.x][temp.y].S && maze[temp.x][temp.y - 1].weight == -1)
        {
            maze[temp.x][temp.y - 1].weight = tempweight + 1;
            uint8_t y = temp.y - 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x, temp.y - 1, buf);
            BFS.push({temp.x, y});
        }
        if (temp.x - 1 >= 0 && !maze[temp.x][temp.y].W && maze[temp.x - 1][temp.y].weight == -1)
        {
            maze[temp.x - 1][temp.y].weight = tempweight + 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x - 1, temp.y, buf);
            uint8_t x = temp.x - 1;
            BFS.push({x, temp.y});
        }
    }
}

/**
 * @brief Sets the north wall for a given point.
 * @param point The point for which the north wall is set.
 */
static void setnorthwall(point point)
{
    maze[point.x][point.y].N = 1;
    API::setWall(point.x, point.y, 'n');
    fprintf(stderr, "Set north wall at (%d, %d)\n", point.x, point.y);

    if (point.y < 15)
    {
        maze[point.x][point.y + 1].S = 1;
        API::setWall(point.x, point.y + 1, 's');
        fprintf(stderr, "Set south wall at (%d, %d)\n", point.x, point.y + 1);
    }
    else
    {
        fprintf(stderr, "Cannot set south wall; out of bounds for (%d, %d)\n", point.x, point.y);
    }
}

/**
 * @brief Sets the south wall for a given point.
 * @param point The point for which the south wall is set.
 */
static void setsouthwall(point point)
{
    maze[point.x][point.y].S = 1;
    API::setWall(point.x, point.y, 's');
    fprintf(stderr, "Set south wall at (%d, %d)\n", point.x, point.y);

    if (point.y > 0)
    {
        maze[point.x][point.y - 1].N = 1;
        API::setWall(point.x, point.y - 1, 'n');
        fprintf(stderr, "Set north wall at (%d, %d)\n", point.x, point.y - 1);
    }
    else
    {
        fprintf(stderr, "Cannot set north wall; out of bounds for (%d, %d)\n", point.x, point.y);
    }
}

/**
 * @brief Sets the west wall for a given point.
 * @param point The point for which the west wall is set.
 */
static void setwestwall(point point)
{
    maze[point.x][point.y].W = 1;
    API::setWall(point.x, point.y, 'w');
    fprintf(stderr, "Set west wall at (%d, %d)\n", point.x, point.y);

    if (point.x > 0)
    {
        maze[point.x - 1][point.y].E = 1;
        API::setWall(point.x - 1, point.y, 'e');
        fprintf(stderr, "Set east wall at (%d, %d)\n", point.x - 1, point.y);
    }
    else
    {
        fprintf(stderr, "Cannot set east wall; out of bounds for (%d, %d)\n", point.x, point.y);
    }
}

/**
 * @brief Sets the east wall for a given point.
 * @param point The point for which the east wall is set.
 */
static void seteastwall(point point)
{
    maze[point.x][point.y].E = 1;
    API::setWall(point.x, point.y, 'e');
    fprintf(stderr, "Set east wall at (%d, %d)\n", point.x, point.y);

    if (point.x < 15)
    {
        maze[point.x + 1][point.y].W = 1;
        API::setWall(point.x + 1, point.y, 'w');
        fprintf(stderr, "Set west wall at (%d, %d)\n", point.x + 1, point.y);
    }
    else
    {
        fprintf(stderr, "Cannot set west wall; out of bounds for (%d, %d)\n", point.x, point.y);
    }
}

/**
 * @brief Sets walls based on the current direction of the bot.
 */
void setwalls()
{
    // Set walls based on current direction
    if (direction == 'n')
    {
        if (API::wallLeft())
        {
            setwestwall(current);
        }
        if (API::wallRight())
        {
            seteastwall(current);
        }
        if (API::wallFront())
        {
            setnorthwall(current);
        }
    }
    else if (direction == 'e')
    {
        if (API::wallLeft())
        {
            setnorthwall(current);
        }
        if (API::wallRight())
        {
            setsouthwall(current);
        }
        if (API::wallFront())
        {
            seteastwall(current);
        }
    }
    else if (direction == 's')
    {
        if (API::wallLeft())
        {
            seteastwall(current);
        }
        if (API::wallRight())
        {
            setwestwall(current);
        }
        if (API::wallFront())
        {
            setsouthwall(current);
        }
    }
    else
    {
        if (API::wallLeft())
        {
            setsouthwall(current);
        }
        if (API::wallRight())
        {
            setnorthwall(current);
        }
        if (API::wallFront())
        {
            setwestwall(current);
        }
    }
}

/**
 * @brief Moves the bot in the specified direction.
 * @param dir The direction to move.
 */
static void realturn(char dir)
{
    switch (dir)
    {
    case 'n':
        current.y++;
        break;
    case 's':
        current.y--;
        break;
    case 'w':
        current.x--;
        break;
    case 'e':
        current.x++;
        break;
    default:
        std::cerr << "Invalid direction" << std::endl;
        break;
    };

    // Determine movement based on current direction
    if (direction == 'n')
    {
        if (dir == 'n')
        {
            API::moveForward();
        }
        else if (dir == 's')
        {
            API::turnRight();
            API::turnRight();
            API::moveForward();
        }
        else if (dir == 'w')
        {
            API::turnLeft();
            API::moveForward();
        }
        else
        {
            API::turnRight();
            API::moveForward();
        }
    }
    else if (direction == 's')
    {
        if (dir == 's')
        {
            API::moveForward();
        }
        else if (dir == 'n')
        {
            API::turnRight();
            API::turnRight();
            API::moveForward();
        }
        else if (dir == 'e')
        {
            API::turnLeft();
            API::moveForward();
        }
        else
        {
            API::turnRight();
            API::moveForward();
        }
    }
    else if (direction == 'w')
    {
        if (dir == 'w')
        {
            API::moveForward();
        }
        else if (dir == 'e')
        {
            API::turnRight();
            API::turnRight();
            API::moveForward();
        }
        else if (dir == 's')
        {
            API::turnLeft();
            API::moveForward();
        }
        else
        {
            API::turnRight();
            API::moveForward();
        }
    }
    else // direction == 'e'
    {
        if (dir == 'e')
        {
            API::moveForward();
        }
        else if (dir == 'w')
        {
            API::turnRight();
            API::turnRight();
            API::moveForward();
        }
        else if (dir == 'n')
        {
            API::turnLeft();
            API::moveForward();
        }
        else
        {
            API::turnRight();
            API::moveForward();
        }
    }
}

/**
 * @brief Performs flood fill to navigate the maze to the destination.
 */
void floodfill()
{
    while (current.x != destination.x || current.y != destination.y)
    {
        std::cerr << "uh!!!" << std::endl;
        // Initialize minimum weight
        char temp_direction;
        uint16_t minweight = 0x7FFF;

        setwalls(); // Set walls around the current position

        // Determine the next move based on minimum weight
        if (!maze[current.x][current.y].N && maze[current.x][current.y + 1].weight < minweight)
        {
            minweight = maze[current.x][current.y + 1].weight;
            temp_direction = 'n';
        }
        if (!maze[current.x][current.y].S && maze[current.x][current.y - 1].weight < minweight)
        {
            minweight = maze[current.x][current.y - 1].weight;
            temp_direction = 's';
        }
        if (!maze[current.x][current.y].W && maze[current.x - 1][current.y].weight < minweight)
        {
            minweight = maze[current.x - 1][current.y].weight;
            temp_direction = 'w';
        }
        if (!maze[current.x][current.y].E && maze[current.x + 1][current.y].weight < minweight)
        {
            minweight = maze[current.x + 1][current.y].weight;
            temp_direction = 'e';
        }
        if (minweight != maze[current.x][current.y].weight - 1)
        {
            reflood(); // Reflood if needed
        }
        else
        {
            realturn(temp_direction); // Move in the determined direction
            direction = temp_direction; // Update direction
        }
    }
}

/**
 * @brief Moves the bot to the destination using flood fill.
 */
void movebot()
{
    initialize_maze({0, 0}, false); // Initialize the maze without resetting
    floodfill(); // Execute flood fill to navigate
}

/**
 * @brief Refloods the maze to reset weights and set up BFS again.
 * @param curr Current point (not used here, just to fit the signature).
 */
static void reflood()
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            maze[i][j].weight = -1; // Reset weights to -1
        }
    }
    
    std::queue<point> BFS; // Queue for BFS
    BFS.push(destination); // Start BFS from the destination
    API::setText(destination.x, destination.y, "0"); // Set text for destination
    maze[destination.x][destination.y].weight = 0; // Set weight of destination

    // BFS to reset weights
    while (!BFS.empty())
    {
        point temp = BFS.front(); // Get front point
        BFS.pop();
        int16_t tempweight = maze[temp.x][temp.y].weight; // Current weight
        char buf[10]; // Buffer for text

        // Look at neighbors with boundary checks
        if (temp.y + 1 < 16 && !maze[temp.x][temp.y].N && maze[temp.x][temp.y + 1].weight == -1)
        {
            maze[temp.x][temp.y + 1].weight = tempweight + 1; // Update weight
            sprintf(buf, "%d", tempweight + 1); // Convert weight to string
            API::setText(temp.x, temp.y + 1, buf); // Set text for neighbor
            uint8_t y = temp.y + 1;
            BFS.push({temp.x, y}); // Push neighbor onto queue
        }
        if (temp.x + 1 < 16 && !maze[temp.x][temp.y].E && maze[temp.x + 1][temp.y].weight == -1)
        {
            maze[temp.x + 1][temp.y].weight = tempweight + 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x + 1, temp.y, buf);
            uint8_t x = temp.x + 1;
            BFS.push({x, temp.y});
        }
        if (temp.y - 1 >= 0 && !maze[temp.x][temp.y].S && maze[temp.x][temp.y - 1].weight == -1)
        {
            maze[temp.x][temp.y - 1].weight = tempweight + 1;
            uint8_t y = temp.y - 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x, temp.y - 1, buf);
            BFS.push({temp.x, y});
        }
        if (temp.x - 1 >= 0 && !maze[temp.x][temp.y].W && maze[temp.x - 1][temp.y].weight == -1)
        {
            maze[temp.x - 1][temp.y].weight = tempweight + 1;
            sprintf(buf, "%d", tempweight + 1);
            API::setText(temp.x - 1, temp.y, buf);
            uint8_t x = temp.x - 1;
            BFS.push({x, temp.y});
        }
    }
}
