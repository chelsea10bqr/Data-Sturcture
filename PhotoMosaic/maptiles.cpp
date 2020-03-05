/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
  MosaicCanvas * c = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
  vector<Point<3>> points;
  std::map<Point<3>, int> tmap;
  //Get array of points based off HSLAPixel
  for(unsigned long it = 0; it < theTiles.size(); it++){
    LUVAPixel average = theTiles[it].getAverageColor();
    points.push_back(Point<3>(convertToXYZ(average)));
    tmap.insert(std::make_pair(points[it], it));
  }
  //Make tree of points
  KDTree<3> myTree = KDTree<3>(points);
  //Set canvas to each point


  for(int i =0; i< c->getRows(); i++){
    for(int j=0; j< c->getColumns(); j++){
      LUVAPixel avg = theSource.getRegionColor(i, j);
      Point<3> avgPoint = convertToXYZ(avg);
      Point<3> nearestPoint = myTree.findNearestNeighbor(avgPoint);

      // Check to ensure the point exists in the map
      map< Point<3>, int >::iterator it = tmap.find(nearestPoint);
      if (it == tmap.end())
          cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;
      int idx = tmap[nearestPoint];
      c->setTile(i, j, &theTiles[idx]);
    }
  }
 return c;


}
