#ifndef IMAGE_FUNCTIONS_H
#define IMAGE_FUNCTIONS_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "image_parameters.h"
#include "image_structs.h"

using namespace std;
using namespace cv; 

//detect features in the image ... need more explaining here .. 
Mat image_detect( Mat const & src, 
		  cascade_t * cascades,
		  int cascade_count,
		  string filename);

//(x,y) are upper left corner of the input img
//figure out how to do the return value
Mat image_crop(Mat const &img,int x, int y, int width, int height);

Mat image_resize(Mat const &in, int width, int height);


//functions to determine image sharpness
//these are just autofocus

//short GetSharpness(char* data, unsigned int width, unsigned int height)
double MaxOfLaplacian(const cv::Mat& src);

// OpenCV port of 'LAPM' algorithm (Nayar89)
double modifiedLaplacian(const cv::Mat& src);

// OpenCV port of 'LAPV' algorithm (Pech2000)
double varianceOfLaplacian(const cv::Mat& src);

// OpenCV port of 'TENG' algorithm (Krotkov86)
double tenengrad(const cv::Mat& src, int ksize);

// OpenCV port of 'GLVN' algorithm (Santos97)
double normalizedGraylevelVariance(const cv::Mat& src);


//----------------------------------------------
Mat image_histo(Mat const &img);

Mat image_GetSkin(Mat const &src);
float image_countSkin(Mat const &src);  //returns percentage of skin pixels


Mat make_picture( Mat const & src, Rect object, int out_width, int out_height, int scale);

#endif
