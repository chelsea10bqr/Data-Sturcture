#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  cs225::Image alma;
  cs225::Image i;
  cs225::Image google;
  cs225::Image chelsea;
  cs225::Image offwhite;
  cs225::Image symbol;
  offwhite.readFromFile("offwhite.png");
  alma.readFromFile("alma.png");
  i.readFromFile("i.png");
  google.readFromFile("google.png");
  chelsea.readFromFile("chelsea.png");
  symbol.readFromFile("symbol.png");
  i.scale(0.2);
  symbol.scale(0.15);
  offwhite.scale(0.05);
  chelsea.scale(0.4);
  offwhite.lighten(0.1);
  cs225::StickerSheet sheet(alma, 5);
  sheet.addSticker(offwhite,400,210);
  sheet.addSticker(chelsea, 550, 95);
  sheet.addSticker(i,300, 95 );
  sheet.addSticker(symbol,410,115);
  sheet.addSticker(google,400,500);
  sheet.render().writeToFile("myImage.png");



  return 0;
}
