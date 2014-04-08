
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//  CV_BGR2HLS, CV_RGB2HLS, CV_HLS2BGR, CV_HLS2RGB CV_BGR2YCrCb CV_BGR2YCrCb,
//  CV_RGB2YCrCb, CV_YCrCb2BGR, CV_YCrCb2RGB


Mat image_histo(Mat const &img)
{   
  vector<Mat> channels; 
  Mat img_hist_equalized;
  
#if 0
  cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format  
  split(img_hist_equalized,channels); //split the image into channels  
  equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)  
  merge(channels,img_hist_equalized); //merge 3 channels including the modified 1st channel into one image  
  cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)
#endif  

#if 1

  //hue or something is only 7-bit so need to check this
  //channel[0] is hue
  //channel[1] is lum
  //channel[2] is sat

  //
  // OpenCV scales the YCrCb components, so that they
    // cover the whole value range of [0,255], so there's
    // no need to scale the values:
    //   cvtColor(src, src_ycrcb, CV_BGR2YCrCb);
    // OpenCV scales the Hue Channel to [0,180] for
    // 8bit images, so make sure we are operating on
    // the full spectrum from [0,360] by using floating
    // point precision:
    //   src.convertTo(src_hsv, CV_32FC3);
    //   cvtColor(src_hsv, src_hsv, CV_BGR2HSV);
    // Now scale the values between [0,255]:
    //   normalize(src_hsv, src_hsv, 0.0, 255.0, NORM_MINMAX, CV_32FC3);


  cvtColor(img, img_hist_equalized, CV_BGR2HLS); 
  split(img_hist_equalized,channels); 
  //should put some form of range in here instead of 0-255 .... 
  equalizeHist(channels[2], channels[2]); //this is Hue or saturate .... need to understand color space better
  merge(channels,img_hist_equalized); 
  cvtColor(img_hist_equalized, img_hist_equalized, CV_HLS2BGR);

#endif


  return  img_hist_equalized ;
}
