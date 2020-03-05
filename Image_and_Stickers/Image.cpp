#include "Image.h"
#include <iostream>
#include <string>
#include <cmath>
#include "cs225/HSLAPixel.h"
using namespace std;
namespace cs225{
  void Image::lighten(){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.l+0.1<=1&&pixel.l>=0){
          pixel.l=pixel.l+0.1;
        }else{
          pixel.l=1;
        }
      }
    }
  }
  void Image::lighten(double amount){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.l+amount<=1&&pixel.l>0){
          pixel.l=pixel.l+amount;
        }else{
          pixel.l=1;
        }
      }
    }
  }
  void Image::darken(){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.l>=0.1&&pixel.l<=1){
          pixel.l=pixel.l-0.1;
        }else{
          pixel.l=0;
        }
      }
    }
  }
  void Image::darken(double amount){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.l-amount>=0&&pixel.l<=1){
          pixel.l=pixel.l-amount;
        }else{
          pixel.l=0;
        }
      }
    }
  }
  void Image::saturate(){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.s<=0.9&&pixel.s>0){
          pixel.s=pixel.s+0.1;
        }else{
          pixel.s=1;
        }
      }
    }
  }
  void Image::saturate(double amount){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.s+amount<=1&&pixel.s>0){
          pixel.s=pixel.s+amount;
        }else{
          pixel.s=1;
        }
      }
    }
  }
  void Image::desaturate(){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.s>=0.1&&pixel.s<=1){
          pixel.s=pixel.s-0.1;
        }else{
          pixel.s=0;
        }
      }
    }
  }
  void Image::desaturate(double amount){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.s-amount>=0&&pixel.s<=1){
          pixel.s=pixel.s-amount;
        }else{
          pixel.s=0;
        }
      }
    }
  }
  void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x, y);
        pixel.s = 0;
      }
    }
  }
  void Image::rotateColor(double degrees){
    unsigned int x,y;
    for (x = 0; x < width(); x++) {
      for (y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if(pixel.h+degrees>360){
          pixel.h = pixel.h+degrees-360;
        }else if(pixel.h+degrees<0){
          pixel.h = 360+(pixel.h+degrees);
        }else{
          pixel.h = pixel.h+degrees;
        }
      }
    }
  }
  void Image::illnify(){
    for (unsigned int x = 0; x < width(); x++) {
      for (unsigned int y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        if (pixel.h>=294)
        {
          pixel.h = 11;
        } else if(abs(pixel.h-11)>=abs(pixel.h-216))
        {
          pixel.h = 216;
        }
        else{
          pixel.h = 11;
        }
      }
    }
  }
  void Image::scale(double factor){
    if (factor>1){
    resize(width()*factor,height()*factor);
    for (int x = width()-1;x>=0; x--) {
      for (int y = height()-1;y>=0; y--) {
        getPixel(x,y)=getPixel((int)x/factor,(int)y/factor);
            }
          }
        }else if(factor<1){

            for (int x = 0; x < width()*factor; x++) {
              for (int y = 0; y < height()*factor; y++) {
                double total_h=0;
                double total_l=0;
                double total_s=0;
                double total_a=0;
                int z = 0 ;
                for(unsigned int j = x*(1/factor);j<x*(1/factor)+1/factor&&j<width();j++){
                  for(unsigned int k =y*(1/factor);k<y*(1/factor)+1/factor&&k<height();k++){
                    HSLAPixel & pixel = getPixel(j,k);
                    total_h = pixel.h+total_h;
                    total_l = pixel.l+total_l;
                    total_s = pixel.s+total_s;
                    total_a = pixel.a+total_a;
                    z++;
                  }
                }
                double ave_h = total_h/z;
                double ave_s = total_s/z;
                double ave_l = total_l/z;
                double ave_a = total_a/z;
                HSLAPixel & s = getPixel(x,y);
                s.l = ave_l;
                s.h = ave_h;
                s.s = ave_s;
                s.a = ave_a;
              }
            }
            resize(width()*factor,height()*factor);
          }


  }
  void Image::scale(unsigned w,unsigned h){
    double factor_w=(double)w/(double)width();
    Image::scale(factor_w);

}
}
