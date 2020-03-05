/* Your code here! */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include "dsets.h"

using namespace std;
using namespace cs225;

class SquareMaze{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
		PNG * drawMaze() const;
		PNG * drawMazeWithSolution();
		PNG * drawCreativeMaze();
	private:
		int width_ = 0;
		int height_ = 0;
		DisjointSets detect;
		vector<int> maze;

};
