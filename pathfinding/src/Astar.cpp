#include "../include/Astar.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include<cstdio>
#include<stack>
// Custom hash and equality for point
struct PointHash {
    size_t operator()(const point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

struct PointEqual {
    bool operator()(const point& a, const point& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

typedef struct {
    point curr;
    point parent;
    std::string direction;
    float weight;
} meta_data;
typedef struct{
    point location;
    std::string direction;
} astar_mouse;

astar_mouse redieeem;
// Compare struct for priority queue
struct Compare {
    bool operator()(const meta_data& a, const meta_data& b) {
        return a.weight > b.weight; // Min-queue
    }
};

// A* data structures
std::unordered_map<point, meta_data, PointHash, PointEqual> map;
std::priority_queue<meta_data, std::vector<meta_data>, Compare> queue;
std::stack<std::string> stack;
point destination;
float Kh = 1;

float get_heuristic(point x) {
    float length = destination.x - x.x;
    float height = destination.y - x.y;
    return Kh * sqrt(length * length + height * height); // Euclidean distance
}
static void print_to_file(const char* filea) {
    
    FILE* file = fopen(filea, "w");
    if (!file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    // Rotate the array 90 degrees counterclockwise while printing
    for (int j = 32; j >= 0; j--) { // Columns of the original array (reversed)
        for (int i = 0; i < 33; i++) { // Rows of the original array
            // fprintf(file, "%lf\t", maze[i][j].weight);
            fprintf(file, "%d\t", maze[i][j].visited);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    // exit(1);
}
void realturn(std::string direction){
    if(redieeem.direction == "n"){
        if(direction == "n"){
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "w"){
        if(direction == "w"){
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "s"){
        if(direction == "s"){
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "e"){
        if(direction == "e"){
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "ne"){
        if(direction == "ne"){
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "nw"){
        if(direction == "nw"){
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "sw"){
        if(direction == "sw"){
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "se"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == "se"){
        if(direction == "se"){
            API::moveForwardHalf();
        }
        else if(direction == "nw"){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "sw"){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == "ne"){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == "e"){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "s"){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == "n"){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == "w"){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else{
        exit(1);
    }
    redieeem.direction = direction;
}
void Astar(uint8_t x, uint8_t y) {
    redieeem.location.x = mouse.location.x;
    redieeem.location.y = mouse.location.y;
    redieeem.direction = std::string(1,mouse.direction);
    destination.x = x;
    destination.y = y;
    std::string aoeu = "/Users/arunfelix/Documents/projects/Micromouse-2024-2025/pathfinding/mazedebug.txt";
    print_to_file(aoeu.c_str());
    meta_data start = {{1, 1}, {1, 1}, "-", 0.0};
    queue.push(start);
    map[start.curr] = start;

    while (!queue.empty()) {
        meta_data point = queue.top();
        queue.pop();
        // fprintf(stderr,"Exploring node (%d,%d) with weight %f\n",point.curr.x,point.curr.y,point.weight);
        if (point.curr.x == destination.x && point.curr.y == destination.y){
            
            break;
        }

        x = point.curr.x;
        y = point.curr.y;

        auto process_neighbor = [&](int nx, int ny, const std::string& dir) {
            // fprintf(stderr,"point (%d,%d): %s\n",nx,ny,maze[nx][ny].visited ? "Visited" : "Not visited"); 
            if (nx >= 0 && nx < 33 && ny >= 0 && ny < 33 && maze[nx][ny].visited) {
                meta_data neighbor;
                neighbor.curr = {static_cast<uint8_t>(nx), static_cast<uint8_t>(ny)};
                neighbor.parent = point.curr;
                neighbor.weight = point.weight + 0.5 + get_heuristic(neighbor.curr);
                neighbor.direction = dir;
                if (map.find(neighbor.curr) == map.end() || neighbor.weight < map[neighbor.curr].weight) {
                    map[neighbor.curr] = neighbor;
                    queue.push(neighbor);
                }
            }
        };

        // Process all neighbors
        process_neighbor(x, y + 1, "n");
        process_neighbor(x, y - 1, "s");
        process_neighbor(x + 1, y, "e");
        process_neighbor(x - 1, y, "w");
        process_neighbor(x + 1, y + 1, "ne");
        process_neighbor(x - 1, y + 1, "nw");
        process_neighbor(x + 1, y - 1, "se");
        process_neighbor(x - 1, y - 1, "sw");
    }
    std::cerr<<"A star end"<<std::endl;
    // Backtracking
    if (map.find(destination) == map.end()) {
        std::cerr << "No path found to destination." << std::endl;
        return;
    }

    meta_data back_boi = map[destination];
    while (back_boi.curr.x != 1 || back_boi.curr.y != 1) {
        stack.push(back_boi.direction);
        if (map.find(back_boi.parent) == map.end()) {
            std::cerr << "Error: Backtracking failed, parent not found!" << std::endl;
            return;
        }
        back_boi = map[back_boi.parent];
    }
    // fprintf(stderr,"mouse current direction: %c\n",mouse.direction);
    // exit(1);
    while(!stack.empty()){
        // std::cerr<<stack.top()<<std::endl;
        realturn(stack.top());
        stack.pop();
    }
}
