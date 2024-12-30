#include "../include/floodfill.h"
#include "../include/API.h"
#include<queue>
#include<cstdio>


cell maze[33][33]; // Center is 14, 14
mouse_t mouse;
point dest;
int i = 0;
void stall(){
    API::turnLeft();
    API::turnLeft();
    API::turnLeft();
    API::turnLeft();
}

static void fill_maze(){
    char buf[50];
    for(int i = 1; i < 33; i += 2){
        for(int j = 1; j < 33; j += 2){
            snprintf(buf,sizeof(buf),"%.1lf",maze[i][j].weight);
            API::setText(i/2,j/2,buf);
        }
    }
}



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

void reflood() {
    std::queue<point> myqueue;
    myqueue.push(dest);

    // Reset weights except for blocked cells
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 33; j++) {
            if (maze[i][j].weight != -2) {
                maze[i][j].weight = INFINITY;
            }
        }
    }

    maze[dest.x][dest.y].weight = 0;

    while (!myqueue.empty()) {
        point temp = myqueue.front();
        myqueue.pop();

        // Look at neighbors
        if (temp.y + 1 < 33 && !hasnorthwall(temp) && maze[temp.x][temp.y].weight + 0.5 < maze[temp.x][temp.y + 1].weight) {
            maze[temp.x][temp.y + 1].weight = maze[temp.x][temp.y].weight + 0.5;
            myqueue.push({temp.x, static_cast<uint8_t>(temp.y + 1)});
        }
        if (temp.y > 0 && !hassouthwall(temp) && maze[temp.x][temp.y].weight + 0.5 < maze[temp.x][temp.y - 1].weight) {
            maze[temp.x][temp.y - 1].weight = maze[temp.x][temp.y].weight + 0.5;
            myqueue.push({temp.x, static_cast<uint8_t>(temp.y - 1)});
        }
        if (temp.x + 1 < 33 && !haseastwall(temp) && maze[temp.x][temp.y].weight + 0.5 < maze[temp.x + 1][temp.y].weight) {
            maze[temp.x + 1][temp.y].weight = maze[temp.x][temp.y].weight + 0.5;
            myqueue.push({static_cast<uint8_t>(temp.x + 1), temp.y});
        }
        if (temp.x > 0 && !haswestwall(temp) && maze[temp.x][temp.y].weight + 0.5 < maze[temp.x - 1][temp.y].weight) {
            maze[temp.x - 1][temp.y].weight = maze[temp.x][temp.y].weight + 0.5;
            myqueue.push({static_cast<uint8_t>(temp.x - 1), temp.y});
        }
    }

    fill_maze();
    // char buf[50];
    // snprintf(buf,sizeof(buf),"../maze%d.txt",i++);
    // print_to_file(buf);
    fprintf(stderr, "Reflood %d complete.\n",i - 1);
}



void initialize_maze(uint8_t x, uint8_t y, bool reset) {
    dest.x = x;
    dest.y = y;
    std::queue<point> myqueue;

    if (reset) {
        for (int i = 0; i < 33; i++) {
            for (int j = 0; j < 33; j++) {
                maze[i][j].weight = -1;
            }
        }
        mouse.location.x = mouse.location.y = 1;
        mouse.direction = 'n';
    }
    else{
        for (int i = 0; i < 33; i++) {
            for (int j = 0; j < 33; j++) {
                if(maze[i][j].weight != -2){
                    maze[i][j].weight = -1;
                }
            }
        }  
    }

    myqueue.push(dest);
    maze[dest.x][dest.y].weight = 0.0;

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

    for(int i = 0; i < 33; i++){
        maze[i][0].weight = -2;
        maze[i][32].weight = -2;
        maze[0][i].weight = -2;
        maze[32][i].weight = -2;
        API::setWall(i/2,0,'s');
        API::setWall(i/2,15,'n');
        API::setWall(0,i/2,'w');
        API::setWall(15,i/2,'e');
    }

    // for (int i = 0; i < 33; i++) {
    //     for (int j = 0; j < 33; j++) {
    //         printf("%.2f  ", maze[i][j].weight);
    //     }
    //     printf("\n");
    // }
    fill_maze();
}

static void setwalls(mouse_t mike) {
    // fprintf(stderr, "Setting walls for mouse at (%d, %d) facing %c\n", mike.location.x, mike.location.y, mike.direction);

    if (mike.direction == 'n') {
        if (API::wallLeft()) {
            // fprintf(stderr, "Wall detected on the left (west) at (%d, %d).\n", mike.location.x - 1, mike.location.y);
            maze[mike.location.x - 1][mike.location.y].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'w');
        }
        if (API::wallRight()) {
            // fprintf(stderr, "Wall detected on the right (east) at (%d, %d).\n", mike.location.x + 1, mike.location.y);
            maze[mike.location.x + 1][mike.location.y].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'e');
        }
        if (API::wallFront()) {
            // fprintf(stderr, "Wall detected in front (north) at (%d, %d).\n", mike.location.x, mike.location.y + 1);
            maze[mike.location.x][mike.location.y + 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'n');
        }
    } else if (mike.direction == 's') {
        if (API::wallLeft()) {
            // fprintf(stderr, "Wall detected on the left (east) at (%d, %d).\n", mike.location.x + 1, mike.location.y);
            maze[mike.location.x + 1][mike.location.y].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'e');
        }
        if (API::wallRight()) {
            // fprintf(stderr, "Wall detected on the right (west) at (%d, %d).\n", mike.location.x - 1, mike.location.y);
            maze[mike.location.x - 1][mike.location.y].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'w');
        }
        if (API::wallFront()) {
            // fprintf(stderr, "Wall detected in front (south) at (%d, %d).\n", mike.location.x, mike.location.y - 1);
            maze[mike.location.x][mike.location.y - 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 's');
        }
    } else if (mike.direction == 'e') {
        if (API::wallLeft()) {
            // fprintf(stderr, "Wall detected on the left (north) at (%d, %d).\n", mike.location.x, mike.location.y + 1);
            maze[mike.location.x][mike.location.y + 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'n');
        }
        if (API::wallRight()) {
            // fprintf(stderr, "Wall detected on the right (south) at (%d, %d).\n", mike.location.x, mike.location.y - 1);
            maze[mike.location.x][mike.location.y - 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 's');
        }
        if (API::wallFront()) {
            // fprintf(stderr, "Wall detected in front (east) at (%d, %d).\n", mike.location.x + 1, mike.location.y);
            maze[mike.location.x + 1][mike.location.y].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'e');
        }
    } else if (mike.direction == 'w') {
        if (API::wallLeft()) {
            // fprintf(stderr, "Wall detected on the left (south) at (%d, %d).\n", mike.location.x, mike.location.y - 1);
            maze[mike.location.x][mike.location.y - 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 's');
        }
        if (API::wallRight()) {
            // fprintf(stderr, "Wall detected on the right (north) at (%d, %d).\n", mike.location.x, mike.location.y + 1);
            maze[mike.location.x][mike.location.y + 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x + 1][mike.location.y + 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'n');
        }
        if (API::wallFront()) {
            // fprintf(stderr, "Wall detected in front (west) at (%d, %d).\n", mike.location.x - 1, mike.location.y);
            maze[mike.location.x - 1][mike.location.y].weight = -2;
            maze[mike.location.x - 1][mike.location.y + 1].weight = -2;
            maze[mike.location.x - 1][mike.location.y - 1].weight = -2;
            API::setWall(mike.location.x / 2, mike.location.y / 2, 'w');
        }
    }

    // fprintf(stderr, "Wall setting complete for direction %c.\n", mike.direction);
}

static void realturn(char direction){
    if(mouse.direction == 'n'){
        if(direction == 'n'){
            API::moveForward();
            mouse.location.y += 2;
        }
        else if(direction == 'e'){
            API::turnRight();
            API::moveForward();
            mouse.location.x += 2;
        }
        else if(direction == 's'){
            API::turnRight();
            API::turnRight();
            API::moveForward();
            mouse.location.y -= 2;
        }
        else if(direction == 'w'){
            API::turnLeft();
            API::moveForward();
            mouse.location.x -= 2;
        }
    }
    else if(mouse.direction == 'e'){
        if(direction == 'e'){
            API::moveForward();
            mouse.location.x += 2;
        }
        else if(direction == 's'){
            API::turnRight();
            API::moveForward();
            mouse.location.y -= 2;
        }
        else if(direction == 'w'){
            API::turnRight();
            API::turnRight();
            API::moveForward();
            mouse.location.x -= 2;
        }
        else if(direction == 'n'){
            API::turnLeft();
            API::moveForward();
            mouse.location.y += 2;
        }
    }
    else if(mouse.direction == 's'){
        if(direction == 's'){
            API::moveForward();
            mouse.location.y -= 2;
        }
        else if(direction == 'w'){
            API::turnRight();
            API::moveForward();
            mouse.location.x -= 2;
        }
        else if(direction == 'n'){
            API::turnRight();
            API::turnRight();
            API::moveForward();
            mouse.location.y += 2;
        }
        else if(direction == 'e'){
            API::turnLeft();
            API::moveForward();
            mouse.location.x += 2;
        }
    }
    else if(mouse.direction == 'w'){
        if(direction == 'w'){
            API::moveForward();
            mouse.location.x -= 2;
        }
        else if(direction == 'n'){
            API::turnRight();
            API::moveForward();
            mouse.location.y += 2;
        }
        else if(direction == 'e'){
            API::turnRight();
            API::turnRight();
            API::moveForward();
            mouse.location.x += 2;
        }
        else if(direction == 's'){
            API::turnLeft();
            API::moveForward();
            mouse.location.y -= 2;
        }
    }
    mouse.direction = direction;
    //fprintf(stderr,"(%d,%d) direction: %c\n",mouse.location.x,mouse.location.y,mouse.direction);
}

void set_visited(point p){
    maze[p.x][p.y].visited = true;
}
void floodfill() {
    //fprintf(stderr, "Starting floodfill. Initial mouse position: (%d, %d). Destination: (%d, %d).\n", mouse.location.x, mouse.location.y, dest.x, dest.y);

    while (mouse.location.x != dest.x || mouse.location.y != dest.y) {
        //fprintf(stderr, "Mouse position: (%d, %d).\n", mouse.location.x, mouse.location.y);
        setwalls(mouse);
        set_visited(mouse.location);
        // Find the minimum weight
        float max_weight = INFINITY;
        char dec_direction;
        fprintf(stderr,"------------ITERATION----------------\n");
        // Check north
        if (mouse.location.y < 31 && !hasnorthwall(mouse.location) && maze[mouse.location.x][mouse.location.y + 2].weight < max_weight) {
            max_weight = maze[mouse.location.x][mouse.location.y + 2].weight;
            maze[mouse.location.x][mouse.location.y + 1].visited = 1;
            dec_direction = 'n';
            fprintf(stderr, "North direction has weight %.2f.\n", max_weight);
        }

        // Check south
        if (mouse.location.y > 1 && !hassouthwall(mouse.location) && maze[mouse.location.x][mouse.location.y - 2].weight < max_weight) {
            max_weight = maze[mouse.location.x][mouse.location.y - 2].weight;
            maze[mouse.location.x][mouse.location.y - 1].visited = 1;
            dec_direction = 's';
            fprintf(stderr, "South direction has weight %.2f.\n", max_weight);
        }

        // Check east
        if (mouse.location.x < 31 && !haseastwall(mouse.location) && maze[mouse.location.x + 2][mouse.location.y].weight < max_weight) {
            max_weight = maze[mouse.location.x + 2][mouse.location.y].weight;
            maze[mouse.location.x + 1][mouse.location.y].visited = 1;
            dec_direction = 'e';
            fprintf(stderr, "East direction has weight %.2f.\n", max_weight);
        }

        // Check west
        if (mouse.location.x > 1 && !haswestwall(mouse.location) && maze[mouse.location.x - 2][mouse.location.y].weight < max_weight) {
            max_weight = maze[mouse.location.x - 2][mouse.location.y].weight;
            maze[mouse.location.x - 1][mouse.location.y].visited = 1;
            dec_direction = 'w';
            fprintf(stderr, "West direction has weight %.2f.\n", max_weight);
        }
        // stall();
        fprintf(stderr, "Decided direction: %c with weight %.2f.\n", dec_direction, max_weight);
        if(max_weight != maze[mouse.location.x][mouse.location.y].weight - 1){
            reflood();
        }
        else{
            realturn(dec_direction);
        }
    }
    // print_to_file();
    //fprintf(stderr, "Floodfill complete. Mouse reached destination (%d, %d).\n", dest.x, dest.y);
}
