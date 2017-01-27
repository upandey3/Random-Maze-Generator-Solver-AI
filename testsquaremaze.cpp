/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "png.h"

int main()
{
    SquareMaze m;
 	//m.makeMaze(3, 3);   
	m.makeMaze(50, 50);
    //m.makeMaze(20, 10);
    std::cout << "MakeMaze complete" << std::endl;

    PNG* unsolved = m.drawMaze();
    unsolved->writeToFile("unsolved.png");
    delete unsolved;
    std::cout << "drawMaze complete" << std::endl;

/*    //CanTravel 
   if (m.canTravel(0, 0, 3)) std::cout << "True : Can travel" << std::endl;
    else std::cout << "False : Can not travel" << std::endl;
//  SetWall
    m.setWall(2, 2, 0, false);
    unsolved = m.drawMaze();
    unsolved->writeToFile("wallunsolved.png");
    delete unsolved;
    std::cout << "drawMaze complete with setWall" << std::endl;
*/



    
    std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;
    PNG* solved = m.drawMazeWithSolution();
    solved->writeToFile("solved.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;
    
    return 0;
}
