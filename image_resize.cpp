#include "image_functions.h"

 
//(x,y) are upper left corner;
Mat image_resize(Mat const &in,int width, int height)
{
  Mat out(width,height,in.type());
  resize(in,out,Size(width,height),CV_INTER_CUBIC);
  return out;
}
