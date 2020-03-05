#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
   PNG* original = new PNG();
   original->readFromFile(inputFile);
   unsigned width = original->width();
   unsigned height = original->height();
   PNG* rotate = new PNG(width,height);
   for (unsigned y = 0;  y < height; y++) {
       for (unsigned x = 0; x < width; x++) {
         rotate->getPixel(width-1-x,height-1-y)=original->getPixel(x,y);
        }
      }
  rotate->writeToFile(outputFile);
  delete original;
  delete rotate;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG* my = new PNG(width, height);
  HSLAPixel* black = new HSLAPixel(240,0,0);
  HSLAPixel* red = new HSLAPixel(350,0.8,0.5);
  HSLAPixel* yellow = new HSLAPixel(60,1,0.5);

  for (unsigned y = 0;  y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
       if(x<=266&&x>0)
        my->getPixel(x,y) = *black;
       if(x>266&&x<532)
       my->getPixel(x,y) = *yellow;
       if(x>=532&&x<=800)
       my->getPixel(x,y) = * red;
     }
   }
  return *my ;
}
