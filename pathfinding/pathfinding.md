[return](../README.md)
# Maze Algorithm

## MIT 2024

The maze algorithm failed. It'd, when it refloods at specific points, never work. 


## Cause

Most likely, the setwalls function. It would set a wall at a place where there is no wall, so the bot assumes it is in a 1 x 1 cell.

## Revisions

Instead of manually setting the walls directly, helper functions were used.

```cpp
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

```


## Running Maze Algorithm in simulation

to run:

```
make # compiles the file
./output/main #runs the file
```

This uses the [following simulator](https://github.com/mackorone/mms?tab=readme-ov-file#maze-files)
