#ifndef IMAGE_STRUCTS_H
#define IMAGE_STRUCTS_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

#define FACE           0
#define HEAD_SHOULDERS 1
#define FACE_FEATURES  2
#define BODY           3

enum cascade_type
  {
    face,
    frontal_face,
    side_face,
    head_shoulders,
    face_features,
    body
  };


//make a struct up for the different cascades and options
typedef struct cascade
{

  string cascadeName;
  int    tryflip;
  Scalar color;
  //for detectMultiScale function
  double scale0;
  int group_threshold;
  Size obj_size_threshold;         
  int detect_flags;
  //filter for detected objects
  float skin_threshold;
  int sharpness_threshold;  
  //type of cascade 
  int type;

} cascade_t;



#endif
