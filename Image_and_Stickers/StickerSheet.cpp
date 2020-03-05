#include "StickerSheet.h"
#include <vector>
using namespace std;
namespace cs225{
StickerSheet::StickerSheet(const Image &picture, unsigned max){
   base = picture;
   m = max;
   arr = new Image[m];
   vector<int> xt(m);
   vector<int> yt(m);
   count=0;
}

StickerSheet::~StickerSheet (){
 delete[] arr;
}
StickerSheet::StickerSheet (const StickerSheet &other){
  this->base= other.base;
  this->arr = new Image[other.m];
  this->count = other.count;
  this->xt = other.xt;
  this->yt = other.yt;
  for(unsigned int i =0;i<count;i++){
  this->arr[i]=other.arr[i];
 }
}
const StickerSheet & 	StickerSheet::operator=(const StickerSheet &other){
  this->base= other.base;
  this->arr = new Image[other.m];
  this->count = other.count;
  this->xt = other.xt;
  this->yt = other.yt;
  for(unsigned int i =0;i<count;i++){
  this->arr[i]=other.arr[i];
 }
  return *this;
}
void 	StickerSheet::changeMaxStickers (unsigned max){
   Image* change = new Image[m];
   change = arr;
   arr = new Image[max];
   if(max>count){
   for(unsigned int i=0;i<count;i++){
     arr[i]=change[i];
   }
 }else{
   for(unsigned int i=0;i<max;i++){
     arr[i]= change[i];
   }
   count = max;
 }
   xt.reserve(max);
   yt.reserve(max);
   m=max;
   delete[] change;
}
int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  if(count== m){
    return -1;
  }
  if(x>=base.width()||y>=base.height()){
    return -1;
  }
    arr[count]= sticker;
    xt.push_back(x);
    yt.push_back(y);
    count ++;
  return count-1;

}
bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
 if(index>(count-1))
 {
   return false;
 }
 if(x>=base.width()||y>=base.height()){
   return false;
 }

 xt[index] = x;
 yt[index] = y;
 return true;
}
void 	StickerSheet::removeSticker (unsigned index){
 for(unsigned int i = index;i<count-1;i++){
   arr[i]=arr[i+1];
 }
 xt.erase(xt.begin()+index);
 yt.erase(yt.begin()+index);
 count--;
}

Image * StickerSheet::getSticker (unsigned index) const{
  if(index>(count-1)||count==0)
  {
    return NULL;
  }
return &arr[index];
}
Image 	StickerSheet::render () const{
  Image b= base;

 for(unsigned int i = 0;i<count;i++){
   if(xt[i]+arr[i].width()>b.width()){
     b.scale(xt[i]+arr[i].width(),2);
   }
   if(yt[i]+arr[i].height()>b.height()){
     b.scale(yt[i]+arr[i].height()/b.height());
   }
   for(unsigned int j = xt[i];j<xt[i]+arr[i].width();j++){
     for(unsigned int k = yt[i];k<yt[i]+arr[i].height();k++){
           HSLAPixel & pixel = arr[i].getPixel(j-xt[i],k-yt[i]);
             HSLAPixel & ba =b.getPixel(j,k);
           if(pixel.a!=0){
              ba = pixel;
           }
     }
   }
 }
 return b;
}
}
