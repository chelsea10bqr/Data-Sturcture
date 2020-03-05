#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(PNG png,Point start,double value,ImageTraversal* traversal){
 p = png;
 cur = start;
 starting = cur;
  val = value;
  t = traversal;
  unsigned h = p.height();
  unsigned w = p.width();
  for(unsigned i = 0;i < w*h;i++){
    is.push_back(false);
  }
  if(whether(start)){
    is[start.x+start.y*w]=true;
    ending = false;
  }else{
    ending = true;
  }
  }

  bool ImageTraversal::Iterator::whether(Point pixel){
    if(pixel.x<p.width()&&pixel.y<p.height()){
    HSLAPixel dot = (p.getPixel(starting.x,starting.y));
    HSLAPixel temp = (p.getPixel(pixel.x,pixel.y));
    if(calculateDelta(dot,temp)<val){
      return true;
    }
  }
      return false;

  }
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned w = p.width();
  unsigned h = p.height();
  Point right = Point(cur.x+1,cur.y);
  Point down = Point(cur.x,cur.y+1);
  Point left = Point(cur.x-1,cur.y);
  Point up = Point(cur.x,cur.y-1);
  if(whether(right)){
    t->add(right);
  }
  if(whether(down)){
    t->add(down);
  }
  if(whether(left)){
    t->add(left);
  }
  if(whether(up)){
    t->add(up);
  }
  Point next;
  for(next = t->peek();is[next.x+next.y*w];next= t->pop()){
    if(t->empty()){
      ending = true;
      return *this;
    }
  }
  cur= next;
  is[cur.x+cur.y*w]= true;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return cur;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return(ending != other.ending);
}
