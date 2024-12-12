# Maze Algorithm

This year, we want diagonals, we're fancy people. In order to do this, we need to redo the maze algorithm. Our previous algorithm was floodfill, but it was quite a constraint. 


## Modifications

- The maze needs to be twice as big, to account for the spot between two cells. For this, we need to use floats instead of integer types. 

```cpp
typedef struct{
  float weight;
  point parent;
  bool visited;
} cell;
```

For exploration, we'll use floodfill, and for the final run, we'll use A star to find the destination.

### Encodings

- When we initialize, we initialize everything to -1. 
- We encode walls as -2