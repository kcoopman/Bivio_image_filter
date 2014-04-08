#include "image_functions.h"

//#include <iostream>

//(x,y) are upper left corner;
Mat image_crop(Mat const &in, int x, int y, int width, int height)
{

  Mat out(height,width,in.type()); //height/width/type -> allocate or reallocate
  Mat roi = in(Rect(x,y,width,height));
  roi.copyTo(out);
  //cout << "input  width is " << in.cols  << " height = " << in.rows  << endl;
  //cout << "output width is " << out.cols << " height = " << out.rows << endl;
  return out;
}
