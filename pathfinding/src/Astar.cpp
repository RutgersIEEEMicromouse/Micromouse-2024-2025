#include "../include/Astar.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include<cstdio>
#include<stack>

static uint8_t prev_direct;


#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SW 5
#define W 6
#define NW 7

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
    uint8_t direction;
    float weight;
} meta_data;
typedef struct{
    point location;
    uint8_t direction;
} astar_mouse;

astar_mouse redieeem;

struct Compare {
    bool operator()(const meta_data& a, const meta_data& b) {
        return a.weight > b.weight; // Min-queue
    }
};

std::unordered_map<point, meta_data, PointHash, PointEqual> map;
std::priority_queue<meta_data, std::vector<meta_data>, Compare> queue;
std::stack<uint8_t> stack;
point destination;
float Kh = 1;

float get_heuristic(point x) {
    float length = destination.x - x.x;
    float height = destination.y - x.y;
    return Kh * sqrt(length * length + height * height);
}

void realturn(uint8_t direction){
    if(redieeem.direction == N){
        if(direction == N){
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == W){
        if(direction == W){
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == S){
        if(direction == S){
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == E){
        if(direction == E){
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == NE){
        if(direction == NE){
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == NW){
        if(direction == NW){
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == SW){
        if(direction == SW){
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == SE){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == W){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnRight();
            API::turnRight45();
            API::moveForwardHalf();
        }
    }
    else if(redieeem.direction == SE){
        if(direction == SE){
            API::moveForwardHalf();
        }
        else if(direction == NW){
            API::turnRight();
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == SW){
            API::turnRight();
            API::moveForwardHalf();
        }
        else if(direction == NE){
            API::turnLeft();
            API::moveForwardHalf();
        }
        else if(direction == E){
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == S){
            API::turnRight45();
            API::moveForwardHalf();
        }
        else if(direction == N){
            API::turnLeft();
            API::turnLeft45();
            API::moveForwardHalf();
        }
        else if(direction == W){
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
    redieeem.direction = mouse.direction;
    destination.x = x;
    destination.y = y;
    meta_data start = {{1, 1}, {1, 1}, static_cast<uint8_t>(100), 0.0};
    queue.push(start);
    map[start.curr] = start;
    prev_direct = N;
    uint16_t nodes_explored = 0;
    while (!queue.empty()) {
        meta_data point = queue.top();
        nodes_explored++;
        queue.pop();
        x = point.curr.x;
        y = point.curr.y;
        API::setColor(x/2,y/2,'y');

        auto process_neighbor = [&](int nx, int ny, uint8_t dir) {
            if (nx >= 0 && nx < 33 && ny >= 0 && ny < 33 && maze[nx][ny].visited) {
                meta_data neighbor;
                neighbor.curr = {static_cast<uint8_t>(nx), static_cast<uint8_t>(ny)};
                neighbor.parent = point.curr;
                neighbor.weight = point.weight + 0.5 + get_heuristic(neighbor.curr);
                neighbor.direction = dir;

                if(neighbor.direction != point.direction){
                    neighbor.weight += 5;
                }

                if (map.find(neighbor.curr) == map.end() || neighbor.weight < map[neighbor.curr].weight) {
                    map[neighbor.curr] = neighbor;
                    queue.push(neighbor);
                }
            }
        };

        // Process all neighbors
        process_neighbor(x, y + 1, N);
        process_neighbor(x, y - 1, S);
        process_neighbor(x + 1, y, E);
        process_neighbor(x - 1, y, W);
        process_neighbor(x + 1, y + 1, NE);
        process_neighbor(x - 1, y + 1, NW);
        process_neighbor(x + 1, y - 1, SE);
        process_neighbor(x - 1, y - 1, SW);
    }
    std::cerr<<"A star end"<<std::endl;
    fprintf(stderr,"a star: nodes expanded: %d\n",nodes_explored);
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
    while(!stack.empty()){
        realturn(stack.top());
        stack.pop();
    }
}
