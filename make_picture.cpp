#include "image_functions.h"
#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include "image_parameters.h"
#include "image_structs.h"

using namespace std;
using namespace cv;

static int crop_count = 0 ;

//might just want to pass the rectangle and not center ....
Mat make_picture( Mat const & src, Rect object, int out_width, int out_height, int scale)
{

  Point center(cvRound((object.x + object.width*0.5)*scale),
	       cvRound((object.y + object.height*0.5)*scale));
  
  int upper_x = center.x - (out_width>>1);
  int upper_y = center.y - (out_height>>2);   //0.25*out_height


  if( (upper_x + out_width)  > src.cols)    out_width    =  src.cols - upper_x;
  if( (upper_y + out_height) > src.rows)    out_height   =  src.rows - upper_y;
  
  Mat roi_portrait  = src(Rect(upper_x, upper_y, out_width  , out_height));

  stringstream number;  number << crop_count;
  string faceName_p =  "crop_"+ number.str() + ".png";
  imwrite(faceName_p, roi_portrait);
  crop_count++;
  //imshow("Out Crop", roi_portrait);
  //waitKey();


  return roi_portrait; 

}



