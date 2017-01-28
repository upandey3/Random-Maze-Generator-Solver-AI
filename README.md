# Random-Maze-Generator-Solver

This is the final machine project for my Data Structure and Algorithms class. 
The goal was to build a random maze generator and solver given the height and the width of the maze. 
I implemented this through the use of disjoint sets and graphs. For the maze generator (see makeMaze function
in maze.cpp), I implemented a custom graph class that I used to intantiante the vertices and edges that 
represent the cells and walls(lack of) of the maze respectively. 

Based on the given height and width of the maze, I constructed a maze with the north and east walls and instantiated a
disjoint set object to keep track of unconnected cells. Then modifying the Kruskal algorithm, I used a priory queue that has
all the edges(walls) and pops one at random instead of the one with the least possible weight. I then checked if the removal of the edge 
would create a cycle using the disjoint set object and if it does not, the wall is removed. The maze is thus created. To solve
the maze I used the BFS algorithm and I implemented the draw functions to depict the maze in a file - "solved.png". 

To generate the random maze, run "make" and then "./testsquaremaze". The width and the height of the maze can be set in the 
testsquaremaze.cpp file by changing "makeMaze(50, 50)".


