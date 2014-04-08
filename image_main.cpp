//image_main.cpp written by Kevin Coopman

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include "image_functions.h"
#include "image_parameters.h"
#include "image_structs.h"

using namespace std;
using namespace cv;

//#define SHOW_IMAGES



int main( int argc, const char** argv )
{
  Mat image;            //matrix is colsxrows width/height
  string inputName;
  string outputName;

  //****************************************************************************************************
 //make an array of cascades to detect features in image
  cascade_t cascades[50]; 
  int cascade_count  = 0;


  //read in file -------------------------------------------------------------------------------------
  inputName.assign( argv[1] );
  image = imread( inputName, 1 ); 
  if( image.empty() )
    {
      cout << "could not open " << inputName << endl;
      return 1;
    }  

  //get a metric on how good the image quality is
  Mat gray;
  cvtColor( image, gray, CV_BGR2GRAY );  
  double image_max_sharpness = MaxOfLaplacian(gray);
  cout << "File is : " << inputName << " width=" << image.cols << " height=" << image.rows 
       << " sharpness= " << image_max_sharpness << endl;     


#if 0
  //This tells if the image is valid or not, just autofocus metrics cameras use

  //cout << "MAX  sharpness = " <<  MaxOfLaplacian(gray) << endl;
  // cout << "LAPM sharpness = " <<  modifiedLaplacian(gray) << endl;
    cout << "LAPV sharpness = " <<  varianceOfLaplacian(gray) << endl; //Kevin Likes this one
    //cout << "TENG sharpness = " <<  tenengrad(gray, 5) << endl;
    cout << "GLVN sharpness = " <<  normalizedGraylevelVariance(gray) << endl; //Good also
#endif



  // Available cascades ------------------------------------------------------------------------------------------
  //     haarcascade_eye_tree_eyeglasses.xml   haarcascade_mcs_leftear.xml
  //     haarcascade_eye.xml                   haarcascade_mcs_lefteye.xml
  //     haarcascade_frontalface_alt2.xml      haarcascade_mcs_mouth.xml
  //     haarcascade_frontalface_alt_tree.xml  haarcascade_mcs_nose.xml
  //     haarcascade_frontalface_alt.xml       haarcascade_mcs_rightear.xml
  //     haarcascade_frontalface_default.xml   haarcascade_mcs_righteye.xml
  //     haarcascade_fullbody.xml              haarcascade_mcs_upperbody.xml
  //     haarcascade_lefteye_2splits.xml       haarcascade_profileface.xml
  //     haarcascade_lowerbody.xml             haarcascade_righteye_2splits.xml
  //     haarcascade_mcs_eyepair_big.xml       haarcascade_upperbody.xml
  //     haarcascade_mcs_eyepair_small.xml
  //   

  //face frontal
  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_frontalface_alt2.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = RED;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_frontalface_alt_tree.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = RED;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_frontalface_alt.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = RED;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;
 
  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_frontalface_default.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = RED;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  //face side views
  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "lbpcascade_profileface.xml"; //DETECT FACES ROTED TO RIGHT FACE NEED TO FLIP PICTURE
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = GREEN;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_profileface.xml"; //this gives side views
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = GREEN;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(32, 32);
  cascades[cascade_count].type                     = FACE;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  //upper boy, shoulders and head
  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_upperbody.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = YELLOW;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(128, 128);
  cascades[cascade_count].type                     = HEAD_SHOULDERS;
  cascades[cascade_count].skin_threshold           = 0.02;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "HS.xml";
  cascades[cascade_count].tryflip                  = 1;
  cascades[cascade_count].color                    = YELLOW;
  cascades[cascade_count].scale0                   = 1.05;
  cascades[cascade_count].group_threshold          = 1;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(128, 128);
  cascades[cascade_count].type                     = HEAD_SHOULDERS;
  cascades[cascade_count].skin_threshold           = 0.02;
  cascades[cascade_count++].sharpness_threshold    = SHARPNESS_FACE_THRESHOLD;

  //face features
  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_rightear.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_righteye.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_leftear.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_lefteye.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_eyepair_big.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_eyepair_small.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_mouth.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

  cascades[cascade_count].cascadeName = OPENCV_DATA_DIR + "haarcascade_mcs_nose.xml";
  cascades[cascade_count].tryflip                  = 0;
  cascades[cascade_count].color                    = ORANGE;
  cascades[cascade_count].scale0                   = 1.1;
  cascades[cascade_count].group_threshold          = 2;
  cascades[cascade_count].detect_flags             = 0|CV_HAAR_SCALE_IMAGE;
  cascades[cascade_count].obj_size_threshold       = Size(5, 5);
  cascades[cascade_count].type                     = FACE_FEATURES;
  cascades[cascade_count].skin_threshold           = SKIN_FACE_FEATURE_THRESHOLD;
  cascades[cascade_count++].sharpness_threshold    = 100;

#if 1
    //DETECTION

    cout << "calling image_detect\n";
    Mat faces = image_detect( image, cascades, cascade_count,inputName); 
    imshow( "FaceDetect", faces );
    //   waitKey(0);  


#ifdef SHOW_IMAGES
    imshow( "FaceDetect", faces );
    waitKey(0);  
#endif
#ifdef FILTER_OBJS
    string faceName =   FACES_OUTPUT_DIR + "filter_"+ inputName;
#else
    string faceName =   FACES_OUTPUT_DIR + "no_filter_"+ inputName;
#endif

    imwrite(faceName, faces);
#endif

#if 0
    //HAVE TO MAKE SURE THIS IS WITHIN BOUNDARIES OPENCV DOES NOT CHECK
    //-----------------------------------------------------------------------------------------------------------------
    //CROP the image
    cout << "calling image_crop\n";
    Mat crop = image_crop(image,100,200, 1*DPI, 2*DPI); //width/height 
#ifdef SHOW_IMAGES
    imshow("crop", crop);
#endif
#endif

#if 0
    //-----------------------------------------------------------------------------------------------------------------
    //Resize the image
    cout << "calling image_resize\n";
    Mat out_resize = image_resize(image,3*DPI, 2*DPI); //width/height 
#ifdef SHOW_IMAGES
    imshow( "resize", out_resize );
#endif
    string resizeName =   RESIZE_OUTPUT_DIR + "resize_"+ inputName;
    imwrite(resizeName, out_resize);
#endif

#if 0
    //-----------------------------------------------------------------------------------------------------------------
    //Histogram Equalization
    Mat histo = image_histo(out_resize);
#ifdef SHOW_IMAGES
    imshow( "histo", histo );
#endif
    string histoName =   HISTO_OUTPUT_DIR + "histo_"+ inputName;
    imwrite(histoName, histo);
#endif

#if 0
    //-----------------------------------------------------------------------------------------------------------------
    //Skin Color threshold
    Mat skin = image_GetSkin(out_resize);
#ifdef SHOW_IMAGES
    imshow( "skin", skin );
#endif
    string skinName =   SKIN_OUTPUT_DIR + "skin_"+ inputName;
    imwrite(skinName, skin);
#endif

#if 0
    //-----------------------------------------------------------------------------------------------------------------
    //write the output to file if an outfile name was given
    if( argc >= 3)
      {
	outputName.assign( argv[2] );
	imwrite( outputName, image);
      }
#endif

    //  waitKey(0);  
    destroyAllWindows(); //destroy all open windows

    
    return 0;
}

