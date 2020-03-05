
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("chelsea.png");
  FloodFilledImage image(png);
  DFS dfs2(png, Point(50,100), 0.05);
    HSLAPixel color2(3,1,0.5);
  MyColorPicker my2(color2);
  image.addFloodFill(dfs2,my2);
  Animation animation2 = image.animate(200);
  PNG lastFrame = animation2.getFrame( animation2.frameCount()-1);
  lastFrame.writeToFile("myFloodFill.png");
  animation2.write("myFloodFill.gif");


  return 0;
}
