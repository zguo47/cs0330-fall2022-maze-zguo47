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
