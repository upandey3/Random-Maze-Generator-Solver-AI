/* Your code here! */

#include "maze.h"

SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height)
{
	//Clearing the old maze, if it is not empty
	if (!connected.isEmpty())
	{
		connected.clear();
		maze.vertices.clear();
		maze.edges.clear();
	}
	maze_height = (size_t)height; maze_width = (size_t)width; 
	for (int j = 0 ; j < height ; j++)
	{
		for(int i = 0 ; i < width ; i++)
			maze.vertices[j* width + i] = {i, j};						
	}
	connected.addelements(width * height);
	maze.edges.resize(height*width);
	vector<pair<int, int>> sackofpairs;
	for (int m = 0 ; m < width*height ; m++)
	{
		if (maze.vertices[m].first + 1 < width)
		{
			maze.edges[m].push_back({m, m+1});
			sackofpairs.push_back(maze.edges[m].back());	
		}
		else
			maze.edges[m].push_back({0, 0});
			
		if (maze.vertices[m].second + 1 < height)
		{
			 maze.edges[m].push_back({m, m + width});;
			 sackofpairs.push_back(maze.edges[m].back());	
		}
		else
			maze.edges[m].push_back({0, 0});
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	shuffle (sackofpairs.begin(), sackofpairs.end(), std::default_random_engine(seed));		
	
	while (!sackofpairs.empty())
	{
		pair<int, int>p = sackofpairs.back();
		sackofpairs.pop_back();
		int r1 = connected.find(p.first);
		int r2 = connected.find(p.second);
		//If there are not in the same set, so removing the wall would not make a cycle	
		if (r1 != r2) 	
		{
			connected.setunion(p.first, p.second);
			maze.removeEdge(p);		
		}	
	}
}
bool SquareMaze::canTravel(int x, int y, int dir) const{
	pair<int, int> nowall(-1,-1);
	int key = y * maze_width + x;
	switch (dir)
	{
		case 0: // Check Rightward 
		{
			if (x + 1 < (int)maze_width  && maze.edges[key][0] == nowall)
				return true;
			return false;
		} 
		case 1: // Check Downward
		{
			if (y + 1 < (int)maze_height && maze.edges[key][1] == nowall)
				return true;
			return false;		
		}
		case 2: // Check Leftward
		{
			if (x - 1 >= 0 && maze.edges[key - 1][0] == nowall)
				return true;
			return false;		
		}
		case 3: // Check Upward
		{
			if (y - 1 >= 0 && maze.edges[key - maze_width][1] == nowall)
				return true;
			return false;		
		}

	}
	return false;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){

	int key = y * maze_width + x;
	if (!exists)
		maze.edges[key][dir] = {-1, -1};
	else if (dir == 0)
		maze.edges[key][0] = {key, key+1};
	else if (dir == 1)
		maze.edges[key][1] = {key, key+maze_width};

}
vector<int> SquareMaze::solveMaze(){

	queue<int> Q;
	map<int, int> parent;
	map<int, bool> visited;
	map<int, int> distance;
	int x, y, cell;
	parent[0] = -1;
	distance[0] = 0;
	Q.push(0);
	int bestdistance = 0, bestpoint = 0;
	while (!Q.empty())
	{
		cell = Q.front();
		Q.pop();
		x = maze.vertices[cell].first; y = maze.vertices[cell].second;
		if (y == (int)maze_height - 1)
		{
			if (distance[cell] > bestdistance)
			{
				bestdistance = distance[cell];
				bestpoint = cell;
			}
			else if (distance[cell] == bestdistance && x < maze.vertices[bestpoint].first)
			{
				bestdistance = distance[cell];
				bestpoint = cell;	 
			}
		}
		visited[cell] = true;
		if (canTravel(x, y, 0) && !visited[cell + 1]) //Right
		{	
			Q.push(cell + 1); 
			parent[cell + 1] = cell;
			distance[cell + 1] = distance[cell] + 1; 
		}
		if (canTravel(x, y, 1) && !visited[cell + maze_width]) // Down
		{	
			Q.push(cell + maze_width); 
			parent[cell + maze_width] = cell;
			distance[cell + maze_width] = distance[cell] + 1; 
		}
		if (canTravel(x, y, 2) && !visited[cell - 1]) // Left
		{	
			Q.push(cell - 1); 
			parent[cell - 1] = cell;
			distance[cell - 1] = distance[cell] + 1; 
		}
		if (canTravel(x, y, 3) && !visited[cell - maze_width]) // Up
		{	
			Q.push(cell - maze_width); 
			parent[cell - maze_width] = cell;
			distance[cell - maze_width] = distance[cell] + 1; 
		}

	
	}
	vector<int> path;
	int curr = bestpoint;
	int p = 0;
	while (curr != 0)
	{ 
		auto it = path.begin();
		p = parent[curr];
		if (curr == p + 1) // If curr is right of parent, push 0 
			path.insert(it, 0);
		else if (curr == p + (int)maze_width) // If curr is below parent, push 1 
			path.insert(it, 1); 
		else if (curr == p - 1) // If curr is left of parent, push 2
			path.insert(it, 2);
		else if (curr == p - (int)maze_width) // If curr is above parent, push 3
			path.insert(it, 3);
		curr = p;
	}	
	return path;
}

//void SquareMaze::solveMazeHelper()
PNG * SquareMaze::drawMaze() const{

	PNG * img = new PNG(maze_width*10+1, maze_height*10+1);
	RGBAPixel black(0,0,0);
	for (size_t i = 0; i < img->width() ; i++)
	*((*img)(i, 0)) = black;
	for (size_t i = 0; i < img->height() ; i++)
	*((*img)(0, i)) = black;
	for (size_t i = 1; i <= 9 ; i++)
	*((*img)(i, 0)) = RGBAPixel();
	
	for (auto key: maze.vertices)
	{
		int x = key.second.first; int y = key.second.second;
		pair<int, int> nowall(-1, -1);
		// If Right Wall exists			
		if (maze.edges[key.first][0] != nowall)
		{
			for (int k = 0; k <= 10; k++)
				*((*img)((x+1)*10, y*10 + k)) = black;		
		}
		//If Bottom Wall exists
		if (maze.edges[key.first][1] != nowall)
		{
			for (int k = 0; k <= 10; k++)
				*((*img)(x*10 + k, (y+1)*10)) = black;		
		}	
	}
	return img;	
}

PNG * SquareMaze::drawMazeWithSolution(){
	PNG * img = this->drawMaze();
	vector<int> path = this->solveMaze();
	RGBAPixel red(255,0,0);
	int i = 5, j = 5;

	for (int key : path)
	{
		if (key == 0)
		{
			for (int m = 0; m <= 10; m++)
			*(img->operator()(i + m, j)) = red;
			i += 10;
		}  
		else if (key == 1)
		{
			for (int m = 0; m <= 10; m++)
			*(img->operator()(i, j + m)) = red;
			j += 10;
		}
		else if (key == 2)
		{
			for (int m = 0; m <= 10; m++)
			*(img->operator()(i - m, j)) = red;
			i -= 10;
		}
		else if (key == 3)
		{
			for (int m = 0; m <= 10; m++)
			*(img->operator()(i, j - m)) = red;
			j -= 10;
		}
	}

	RGBAPixel white;
	int x = (i - 5) / 10, y = (j - 5) / 10;

	for (int k = 1 ; k <= 9 ; k ++)
		*(img->operator()(x*10+k, (y+1)*10)) = white; 
	
	return img;
}
void SquareMaze::Graph::removeEdge(pair<int, int> pair)
{	
	if (edges[pair.first][0] == pair)	
			edges[pair.first][0] = {-1,-1};
	else if (edges[pair.first][1] == pair)
			edges[pair.first][1] = {-1,-1};
	
}
