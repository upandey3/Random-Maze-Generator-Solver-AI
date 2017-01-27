/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include <vector>
#include <map>
#include <utility>
#include "png.h"
#include <algorithm>
#include <random>
#include <queue>

using std::map;
using std::vector;
using std::pair;
using std::queue;

class SquareMaze{

public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();
private:
	class Graph{
	public:
		map<int, pair<int, int>> vertices;
		vector<vector<pair<int, int>>> edges; 
		void removeEdge(pair<int, int> pair);
	};
	Graph maze;
	DisjointSets connected; 
	size_t maze_height, maze_width;

};


#endif
