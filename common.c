#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/*
 * Determines whether or not the room at [row][col] is a valid room within the
 *maze with dimensions num_rows x num_cols
 *
 * Parameters:
 *  - row: row of the current room
 *  - col: column of the current room
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *
 * Returns:
 *  - 0 if room is not in the maze, 1 if room is in the maze
 */
int is_in_range(int row, int col, int num_rows, int num_cols) {
    // TODO: implement function
    if (row < num_rows && col < num_cols && row >= 0 && col >= 0){
        return 1;
    }else{
        return 0;
    }
}

/*
 * Given a pointer to the room and a Direction to travel in, return a pointer to
 *the room that neighbors the current room on the given Direction. For example:
 *get_neighbor(&maze[3][4], EAST) should return &maze[3][5]
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - room: pointer to the current room
 *  - dir: Direction to get the neighbor from
 *  - maze: a 2D array of maze_room structs representing your maze
 * Returns:
 *  - pointer to the neighboring room
 */
struct maze_room *get_neighbor(int num_rows, int num_cols,
                               struct maze_room maze[num_rows][num_cols],
                               struct maze_room *room, Direction dir) {
    // TODO: implement function
    struct maze_room *next_room;
    int row = room->row;
    int col = room->col;

    if (dir == EAST){
        col += 1;
    }else if (dir == WEST){
        col -= 1;
    }else if (dir == NORTH){
        row -= 1;
    }else if (dir == SOUTH){
        row += 1;
    }

    if (is_in_range(row, col, num_rows, num_cols) == 1){
        next_room = &maze[row][col];
        return next_room;
    }else{
        return NULL;
    }
    
}

/*
 * Initializes a 2D array of maze rooms with all of the necessary values
 *
 * Parameters:
 *  - num_rows: the number of the rows in the maze
 *  - num_cols: the number of columns in the maze
 *  - maze: a 2D array of uninitialized maze_rooms (to be initialized in
 *     this function)
 *
 * Returns:
 *  - nothing (the initialized maze will be stored in the 'maze' array)
 */
void initialize_maze(int num_rows, int num_cols,
           struct maze_room maze[num_rows][num_cols]) {
    // TODO: implement function
    for (int r = 0; r < num_rows; r = r + 1){
        for (int c = 0; c < num_cols; c = c + 1){
            maze[r][c].row = r;
            maze[r][c].col = c;
            maze[r][c].visited = 0;
            maze[r][c].north = 2;
            maze[r][c].south = 2;
            maze[r][c].east = 2;
            maze[r][c].west = 2;
            maze[r][c].next = NULL;
        }
    }
    return;
}

/*
 * A helper function that will assign a given value to a maze_room's field  corresponding to the given direction. 
 *
 * Parameters:
 *  - *r : the maze_room to be assigned value to its field.
 *  - dir: the given direction to determine the field to assign
 *  - n: the given value to be assigned
 *
 * Returns:
 *  - nothing 
 */
void helper(struct maze_room *r, Direction dir, int n){

    if (dir == EAST){
        r->east = n;
    }if (dir == WEST){
        r->west = n;
    }if (dir == NORTH){
        r->north = n;
    }if (dir == SOUTH){
        r->south = n;
    }
}

/*
 * A helper function for drunken_walk. If a given neighbor of the current room has an opening or wall in the opposite of a given direction, store a wall for the current roon in the given direction.
 *
 * Parameters:
 *  - *r: the current maze_room
 *  - *n: the neighbor of the current maze_room
 *  - dir: the given direction
 *
 * Returns:
 *  - nothing
 */
void second_helper(struct maze_room *r, struct maze_room *n, Direction dir){
    if (dir == EAST){
        if (n->west == 0){
            r->east = 0;
        }else{
            r->east = 1;
        }
    }if (dir == WEST){
        if (n->east == 0){
            r->west = 0;
        }else{
            r->west = 1;
        }
    }if (dir == NORTH){
        if (n->south == 0){
            r->north = 0;
        }else{
            r->north = 1;
        }
    }if (dir == SOUTH){
        if (n->north == 0){
            r->south = 0;
        }else{
            r->south = 1;
        }
    }
}



