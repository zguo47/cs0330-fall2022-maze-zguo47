#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "solver.h"

/*
 * Given a pointer to a maze_room, set its connections in all four directions
 *based on the hex value passed in.
 *
 * For example:
 *
 *      create_room_connections(&maze[3][4], 0xb)
 *
 * 0xb is 1011 in binary, which means we have walls on all sides except the
 *WEST. This means that every connection in maze[3][4] should be set to 1,
 *except the WEST connection, which should be set to 0.
 *
 * See the handout for more details about our hexadecimal representation, as
 *well as examples on how to use bit masks to extract information from this
 *hexadecimal representation.
 *
 * Parameters:
 *  - room: pointer to the current room
 *  - hex: hexadecimal integer (between 0-15 inclusive) that represents the
 *connections in all four directions from the given room.
 *
 * Returns:
 *  - nothing. The connections should be saved in the maze_room struct
 *pointed to by the parameter (make sure to use pointers correctly!).
 */
void create_room_connections(struct maze_room *room, unsigned int hex) {
    // TODO: implement this function
    room->north = 0;
    room->south = 0;
    room->west = 0;
    room->east = 0;

    if (hex & 1){
        room->north = 1;
    }
    if (hex & 2){
        room->south = 1;
    }
    if (hex & 4){
        room->west = 1;
    }
    if (hex & 8){
        room->east = 1;
    }
}

/*
 * A helper function for dfs. Return 1 if for a maze_room, on a given direction, there exist a neighbor room that has not been visited. 
 *
 * Parameters:
 *  - *c: the current maze_room
 *  - *n: the neighbor of the current maze_room
 *  - dir: the given direction
 *
 * Returns:
 *  - 1 if there is such neighbor, 0 if otherwise. 
 */
int third_helper(struct maze_room *c, struct maze_room *n, Direction dir){
    if (dir == EAST && c->east == 0 && n->visited == 0){
        return 1;
    }else if (dir == WEST && c->west == 0 && n->visited == 0){
        return 1;
    }else if (dir == SOUTH && c->south == 0 && n->visited == 0){
        return 1;
    }else if (dir == NORTH && c->north == 0 && n->visited == 0){
        return 1;
    }else{
        return 0;
    }
}

/*
 * A helper function that helps get the maze_room with its next field pointing towards the current maze_room. 
 *
 * Parameters:
 *  - num_rows: the number of the rows in the maze
 *  - num_cols: the number of columns in the maze
 *  - maze: a 2D array of uninitialized maze_rooms (to be initialized in
 *     this function)
 *  - *room: the current maze_room
 *
 * Returns:
 *  - the maze_room with its next pointing to the current maze_room. return Null if there is no such room. 
 */
struct maze_room *get_back(int num_rows, int num_cols, struct maze_room maze[num_rows][num_cols], struct maze_room *room){
    Direction directions[4] = { NORTH, SOUTH, EAST, WEST };
    for (int d = 0; d < 4; d++){
        struct maze_room *n;
        n = get_neighbor(num_rows, num_cols, maze, room, directions[d]);
        if (n != NULL && n->next == room){
            return n;
        }
    }
    return NULL;
}

/*
 * Recursive depth-first search algorithm for solving your maze.
 * This function should also print out either every visited room as it goes, or
 * the final pruned solution, depending on whether the FULL macro is set.
 *
 * Note that you may need to add extra parameters to this function's signature,
 * depending on how you choose to store the pruned solution.
 *
 * See handout for more details, as well as a pseudocode implementation.
 *
 * Parameters:
 *  - row: row of the current room
 *  - col: column of the current room
 *  - goal_row: row of the goal room
 *  - goal_col: col of the goal room
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - maze: a 2d array of maze_room structs representing your maze
 *  - file: the file to write the solution to
 *
 * Returns:
 *  - 1 if the current branch finds a valid solution, 0 if no branches are
 *valid.
 */
int dfs(int row, int col, int goal_row, int goal_col, int num_rows,
        int num_cols, struct maze_room maze[num_rows][num_cols], FILE *file) {
    Direction directions[4] = { NORTH, SOUTH, EAST, WEST };
    // TODO: implement this function
    struct maze_room *current; 
    current = &maze[row][col];


    if (row == goal_row && col == goal_col){
        #ifdef FULL
        fprintf(file, "%d,%d\n", row, col);
        #endif
        return 1;
    }

    current->visited = 1;

    #ifdef FULL
    fprintf(file, "%d,%d\n", row, col);
    #endif

    for (int d = 0; d < 4; d++){
        struct maze_room *n;
        n = get_neighbor(num_rows, num_cols, maze, current, directions[d]);
        if (n != NULL && third_helper(current, n, directions[d]) == 1){
            current->next = n;
            if (dfs(n->row, n->col, goal_row, goal_col, num_rows, num_cols, maze, file) == 1){
                return 1;
            }
        }
    }

    #ifdef FULL
    struct maze_room *b;
    b = get_back(num_rows, num_cols, maze, current);
    fprintf(file, "%d,%d\n", b->row, b->col);
    #endif
    return 0;

}




/*
 * Decodes an encoded maze and stores the resulting maze room data in the
 * passed 'maze' variable.
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - maze: a 2d array of maze_room structs (where to store the decoded
 *maze)
 *  - encoded_maze: a 2d array of numbers representing a maze
 *
 * Returns:
 *  - nothing; the decoded maze room is stored in the `maze` variable
 */
void decode_maze(int num_rows, int num_cols,
                 struct maze_room maze[num_rows][num_cols],
                 int encoded_maze[num_rows][num_cols]) {
    // TODO: implement this function
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            struct maze_room *c;
            c = &maze[i][j];
            c->row = i;
            c->col = j;
            c->visited = 0;
            c->next = NULL;
            create_room_connections(c, encoded_maze[i][j]);
        }
    }
}

/*
 * Recursively prints the pruned solution path (using the current maze room
 * and its next pointer)
 *
 * Parameters:
 *  - room: a pointer to the current maze room
 *  - file: the file where to print the path
 *
 * Returns:
 *  - 1 if an error occurs, 0 otherwise
 */
int print_pruned_path(struct maze_room *room, FILE *file) {
    // TODO: implement this function
    if (room->next == NULL){
        fprintf(file, "%d,%d\n", room->row, room->col);
        return 0;
    }
    fprintf(file, "%d,%d\n", room->row, room->col);
    print_pruned_path(room->next, file);
    return 1;

}

/*
 * Reads encoded maze from the file passed in
 *
 * Parameters:
 *  - num_rows: number of rows in the maze
 *  - num_cols: number of columns in the maze
 *  - encoded_maze: a maze_room array as a hexadecimal array based on its
 *    connections
 *  - file_name: input file to read the encoded maze from
 *
 * Returns:
 *  - 1 if an error occurs, 0 otherwise
 */
int read_encoded_maze_from_file(int num_rows, int num_cols,
                                int encoded_maze[num_rows][num_cols],
                                char *file_name) {
    int err = 0;

    // open file
    FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    // read each hex value into 2D array
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            unsigned int encoded_room;
            err = fscanf(f, "%1x", &encoded_room);
            encoded_maze[i][j] = encoded_room;
            if (err < 0) {
                fprintf(stderr, "Reading from file failed");
                return 1;
            }
        }
    }
    // close file
    int close = fclose(f);
    if (close == EOF) {
        fprintf(stderr, "Could not close file.\n");
        return 1;
    }
    return 0;
}

/*
 * Main function
 *
 * Parameters:
 *  - argc: the number of command line arguments - for this function 9
 *  - **argv: a pointer to the first element in the command line
 *            arguments array - for this function:
 *            ["solver", <input maze file>, <number of rows>, <number of
 *columns> <output path file>, <starting row>, <starting column>, <ending row>,
 *<ending column>]
 *
 * Returns:
 *  - 0 if program exits correctly, 1 if there is an error
 */

int main(int argc, char **argv) {
    int num_rows, num_cols, start_row, start_col, goal_row, goal_col;
    char *maze_file_name;
    char *path_file_name;
    if (argc != 9) {
        printf("Incorrect number of arguments.\n");
        printf(
            "./solver <input maze file> <number of rows> <number of columns>");
        printf(" <output path file> <starting row> <starting column>");
        printf(" <ending row> <ending column>\n");
        return 1;
    } else {
        maze_file_name = argv[1];
        num_rows = atoi(argv[2]);
        num_cols = atoi(argv[3]);
        path_file_name = argv[4];
        start_row = atoi(argv[5]);
        start_col = atoi(argv[6]);
        goal_row = atoi(argv[7]);
        goal_col = atoi(argv[8]);
        if (num_rows <= 0 || num_cols <= 0){
            printf("incorrect maze dimensions!");
            return 1;
        }
        if (is_in_range(start_row, start_col, num_rows, num_cols) == 0){
            printf("invalid starting location!");
            return 1;
        }
        if (is_in_range(goal_row, goal_col, num_rows, num_cols) == 0){
            printf("invalid destination location!");
            return 1;
        }
    }


    // TODO: implement this function
    int result[num_rows][num_cols];
    struct maze_room maze[num_rows][num_cols];
    read_encoded_maze_from_file(num_rows, num_cols, result, maze_file_name);
    if (read_encoded_maze_from_file(num_rows, num_cols, result, maze_file_name) == 1){
        exit(1);
    }
    decode_maze(num_rows, num_cols, maze, result);

    FILE *f = fopen(path_file_name, "w+");
    if (f == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    #ifdef FULL
    fprintf(f, "%s\n", "FULL");
    dfs(start_row, start_col, goal_row, goal_col, num_rows, num_cols, maze, f);
    #else
    dfs(start_row, start_col, goal_row, goal_col, num_rows, num_cols, maze, f);
    fprintf(f, "%s\n", "PRUNED");
    struct maze_room *first;
    first = &maze[start_row][start_col];
    print_pruned_path(first, f);
    #endif

    int close = fclose(f);
    if (close == EOF) {
        fprintf(stderr, "Could not close file.\n");
        return 1;
    }
    return 0;

}
