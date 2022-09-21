```
  __  __               
 |  \/  |              
 | \  / | __ _ _______ 
 | |\/| |/ _` |_  / _ \
 | |  | | (_| |/ /  __/
 |_|  |_|\__,_/___\___|
```
In this project, I use four helper functions in total.
First, in generator.c and generator.h, the method void helper(struct maze_room *r, 
Direction dir, int n), which will assign a given value, represented by n, to the 
maze_room r's field corresponding to the given direction, dir. It returns 
nothing, the changes will be stored in the maze_room r. This helper is called in
drunken_walk, to make the method looks more organized.

Second, in generator.c and generator.h, the method void second_helper
(struct maze_room *r, struct maze_room *n, Direction dir), which is another 
helper method for drunken_walk. If a given neighbor of the current room has an 
opening or wall in the opposite of a given direction, store a wall for the 
current roon in the given direction. Returns nothing, the change will be stored
in the field of the current room. 

Third, in solver.c and solver.h the method int third_helper(struct maze_room *c, 
struct maze_room *n, Direction dir), which returns 1 if for a maze_room, on a 
given direction, there exist a neighbor room that has not been visited. This is 
a helper function for dfs, to make the process of determining a valid neighbor 
easier. It will return 0 if the given neighbor is invalid. 

Fourth, in solver.c and solver.h the method struct maze_room *get_back
(int num_rows, int num_cols, struct maze_room maze[num_rows][num_cols], 
struct maze_room *room), which helps get the maze_room with its next field 
pointing towards the current maze_room. If there is no neighbor with its next
field pointing to the given room, it will return NULL. This method is for dfs, 
especially for printing the FULL path, since it needs backtracking. 

My program consists of a generator and a solver. In the generator, it uses the 
drunken_walk algorithum, which is a recursive function that will start from a 
random room, and try to find a valid path by each time finding an unvisited and 
valid neighbor, at random direction, until all rooms in the maze are visited. 
This will make sure that there always exist a path from any room in the maze to
another one. In the solver, I use the dfs algorithum, which is a recursive 
function that will try find a valid path everytime from one direction, change
to another one if there is a dead end, until finding the destination. To print
out the FULL path, I will print out the current location of the room with each
iteration, and also to backtrack, I call the helper get_back after the for loop 
(which is when there is no available path on all four directions) to print out
the room one iteration before. To print the pruned path, I will use the print_
pruned_path method to print out the linked list of rooms from the starting
location, and finding the next to print by looking at the next field for every
room, until the next field is NULL (which means that it reaches the destination
room).
