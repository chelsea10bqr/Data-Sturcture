/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <vector>
#include "cs225/HSLAPixel.h"
#include <math.h>
#include <queue>
#include <map>
#include "cs225/PNG.h"


SquareMaze::SquareMaze(){

}

void SquareMaze::makeMaze(int width, int height){
	maze.clear();
	maze.resize(width * height);
	width_ = width;
	height_ = height;
	for(int i=0; i < width*height; i++){
		maze[i] = 3;
	}
	detect.addelements(width * height);
	while(detect.size(0) < (width * height)){
		int element = rand() % (width * height);
		int r = rand() % 2;
		if(r == 0){
			r = width;
		}
		if((element+1) % width == 0){
			r = width;
		}
		if(element >= width* (height-1)){
			r = 1;
		}
		if(element == width * height -1)
			continue;
		int one = detect.find(element);
		int two = detect.find(element + r);
		if(one != two){
			detect.setunion(one, two);
			if(r == 1){
				setWall(element%width, element/width, 0, false);
			}else{
				setWall(element%width, element/width, 1, false);
			}
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
	if ((0 <= x)&&(x < width_)&&(0 <= y)&&(y < height_)){
		int value = maze[(y*width_) + x];
		if ((dir == 0)&&((x+1) < width_)){
			if (value == 0 || value == 2){
				return true;
			}
		}else if ((dir == 1)&&((y+1) < height_)){
			if (value == 0 || value == 1){
				return true;
			}
		}else if ((dir == 2)&&(0 <= (x-1))){
			if (maze[(y*width_) + x-1] == 0 || maze[(y*width_) + x-1] == 2){
				return true;
			}
		}else if ((dir == 3)&&(0 <= (y-1))){
			if (maze[(y-1)*(width_) + x] == 0 || maze[(y-1)*(width_) + x] == 1){
				return true;
			}
		}
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int value = maze[y*width_+x];
  if(exists){
    if(dir == 0){
      if(value == 0 || value == 1){
        maze[y*width_+x] = 1;
        return;
      }
      else{
        maze[y*width_+x] = 3;
        return;
      }
    }else{
      if(value == 0 || value == 2){
        maze[y*width_+x] = 2;
        return;
      }
      else{
        maze[y*width_+x] = 3;
        return;
      }
    }
  }else{
    if(dir == 0){
      if(value == 3){
        maze[y*width_+x] = 2;
        return;
      }else if (value == 1){
        maze[y*width_+x] = 0;
        return;
      }
    }else{
      if(value == 3){
        maze[y*width_+x] = 1;
        return;
      }else if (value == 2){
        maze[y*width_+x] = 0;
        return;
      }
    }
  }
}

vector<int> SquareMaze::solveMaze(){
  vector<int> best;
  queue<int> q;
  q.push(0);
  std::map<int, int> m;
  m.insert(std::pair<int,int>(0, 0));
  std::map<int, int> parent;
  int count = 0;
  while (!q.empty()){
      int element = q.front();
      q.pop();
      int x = element%width_;
      int y = element/width_;
			if(canTravel(x, y, 0) && m.find(y*width_+x+1) == m.end()){
				q.push((y*width_) + x+1);
				m.insert(std::pair<int, int>(y*width_+x+1, m[element]+1));
				parent.insert(std::pair<int, int>(y*width_+x+1, element));
			}
			if(canTravel(x, y, 1) && m.find((y+1)*width_+x) == m.end()){
				q.push(((y+1)*width_) + x);
				m.insert(std::pair<int, int>((y+1)*width_+x, m[element]+1));
				parent.insert(std::pair<int, int>((y+1)*width_+x, element));
			}
			if(canTravel(x, y, 2) && m.find(y*width_+x-1) == m.end()){
				q.push((y*width_) + x-1);
				m.insert(std::pair<int, int>(y*width_+x-1, m[element]+1));
				parent.insert(std::pair<int, int>(y*width_+x-1, element));
			}
			if(canTravel(x, y, 3) && m.find((y-1)*width_+x) == m.end()){
				q.push(((y-1)*width_) + x);
				m.insert(std::pair<int, int>((y-1)*width_+x, m[element]+1));
				parent.insert(std::pair<int, int>((y-1)*width_+x, element));

      }
	}
	unsigned maxd = 0;
	int bestdest = 0;
	for(int x = 0; x < width_ ; ++x){
		int dest = ((height_-1)*width_) + x;
		vector<int> temp;
		while(dest != 0){
			int reverse = dest - parent[dest];
			if(reverse == 1){
				temp.push_back(0);
			}
			else if(reverse == -1){
				temp.push_back(2);
			}
			else if(reverse == width_){
				temp.push_back(1);
			}
			else if(reverse == -width_){
				temp.push_back(3);
			}
			dest = parent[dest];
		}
		if(maxd < temp.size()){
			maxd = temp.size();
			best = temp;
			bestdest = dest;
		}
	}
  std::reverse(best.begin(), best.end());
  return best;
}

PNG * SquareMaze::drawMaze() const{
  PNG * origin = new PNG(width_*10+1, height_*10+1);
  for(int i = 10; i<width_*10+1; i++){
    HSLAPixel & pixel = origin->getPixel(i, 0);
    pixel.l = 0;
  }
  for(int i=0; i<height_*10+1; i++){
    HSLAPixel & pixel = origin->getPixel(0, i);
    pixel.l = 0;
  }
  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      int value = maze[(y*width_) + x];
      if(value == 3 || value == 1){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& pixel = origin->getPixel((x+1)*10, y*10+k);
          pixel.l = 0;
        }
      }
      if(value == 3 || value == 2){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& pixel = origin->getPixel(x*10+k, (y+1)*10);
          pixel.l = 0;
        }
      }
    }
  }
  return origin;
}

PNG * SquareMaze::drawMazeWithSolution(){
	PNG * sol = drawMaze();
	vector<int> best;
	int x = 5;
  int y = 5;
  best = solveMaze();
	for (int dir : best){
      for (int p = 1; p < 11; ++p){
			HSLAPixel& pixel = sol->getPixel(x,y);
			pixel.h = 0;
			pixel.s = 1;
			pixel.l = 0.5;
			pixel.a = 1;
    	if (dir == 0){
				x++;
			}
			if (dir == 1){
				y++;
			}
			if (dir == 2){
				x--;
			}
			if (dir == 3){
				y--;
			}
		}
		HSLAPixel& pixel = sol->getPixel(x,y);
		pixel.h = 0;
		pixel.s = 1;
		pixel.l = 0.5;
		pixel.a = 1;
	}
	for(int k =1; k < 10; k++){
		HSLAPixel& pixel = sol->getPixel(x+k-5, y+5);
		pixel.l = 1;
	}
  return sol;
}

PNG * SquareMaze::drawCreativeMaze(){
	maze.resize(9*9);
width_ = 9;
height_ = 9;
for(int i = 0;i<81;i++){
	maze[i] = (rand() % (4));
}

PNG * creative = new PNG(width_*10+1, height_*10+1);
for(int x = 0; x < width_*10+1; x++){
	for(int y = 0; y < height_*10+1; y++){
		HSLAPixel & pixel = creative->getPixel(x,y);
		if(pixel.l != 0)
			pixel.h = (rand()%(261-177)+177);
			pixel.s = 1;
			pixel.l = 0.5;
			pixel.a = 1;
		}
	}

	for(int i = 10; i<width_*10+1; i++){
		HSLAPixel & pixel = creative->getPixel(i, 0);
		pixel.l = 0;
	}
	for(int i=0; i<height_*10+1; i++){
		HSLAPixel & pixel = creative->getPixel(0, i);
		pixel.l = 0;
	}
	for(int x = 0; x < width_; x++){
		for(int y = 0; y < height_; y++){
			int value = maze[(y*width_) + x];
			if(value == 3 || value == 1){
				for(int k = 0; k <= 10; k++){
					HSLAPixel& pixel = creative->getPixel((x+1)*10, y*10+k);
					pixel.l = 0;
				}
			}
			if(value == 3 || value == 2){
				for(int k = 0; k <= 10; k++){
					HSLAPixel& pixel = creative->getPixel(x*10+k, (y+1)*10);
					pixel.l = 0;
				}
			}
		}
	}
vector<int> best;
int x = 5;
int y = 5;
best = solveMaze();
for (int dir : best){
		for (int p = 1; p < 11; ++p){//color 11 pixels in a line
		HSLAPixel& pixel = creative->getPixel(x,y);
		pixel.h = 0;
		pixel.s = 1;
		pixel.l = 0.5;
		pixel.a = 1;
		if (dir == 0){
			x++;
		}
		if (dir == 1){
			y++;
		}
		if (dir == 2){
			x--;
		}
		if (dir == 3){
			y--;
		}
	}
	HSLAPixel& pixel = creative->getPixel(x,y);
	pixel.h = 0;
	pixel.s = 1;
	pixel.l = 0.5;
	pixel.a = 1;
}
for(int k =1; k < 10; k++){
	HSLAPixel& pixel = creative->getPixel(x+k-5, y+5);
	pixel.l = 1;
}
return creative;
}
