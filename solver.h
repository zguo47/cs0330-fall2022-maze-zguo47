#include "common.h"

void create_room_connections(struct maze_room *room, unsigned int hex);

int dfs(int row, int col, int goal_row, int goal_col, int num_rows,
        int num_cols, struct maze_room maze[num_rows][num_cols], FILE *file);
        
void decode_maze(int num_rows, int num_cols,
                 struct maze_room maze[num_rows][num_cols],
                 int encoded_maze[num_rows][num_cols]);

int print_pruned_path(struct maze_room *room, FILE *file);

int read_encoded_maze_from_file(int num_rows, int num_cols,
                                int encoded_maze[num_rows][num_cols],
                                char *file_name);

int third_helper(struct maze_room *c, struct maze_room *n, Direction dir);

struct maze_room *get_back(int num_rows, int num_cols, struct maze_room maze[num_rows][num_cols], struct maze_room *room);

