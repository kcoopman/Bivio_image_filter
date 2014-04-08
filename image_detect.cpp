#include "image_functions.h"
#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include "image_parameters.h"
#include "image_structs.h"

using namespace std;
using namespace cv;

//   Some references
//   http://docs.opencv.org/doc/user_guide/ug_traincascade.html
//   http://experienceopencv.blogspot.com/2011/02/hog-descriptor.html
//   http://alereimondo.no-ip.org/OpenCV/34 -> This is GOOD
//   http://www.vision.ee.ethz.ch/~gfanelli/head_pose/head_forest.html
//   http://code.opencv.org/projects/opencv/repository/revisions/master/show/data/haarcascades
//   http://docs.opencv.org/modules/gpu/doc/object_detection.html



//returns the number of objects detected
Mat image_detect( Mat const & src, 
		  cascade_t * cascades,
		  int cascade_count,
		  string filename)
{

  string cascadeName;
  CascadeClassifier cascade; 
  vector<Rect> objects;
  vector<Rect> objects_flip;
  Mat img = src.clone();
  Mat img_draw = src.clone();
  Mat img_group = src.clone();
  int scale = cvRound(src.rows/FACE_DETECT_RESIZE_WIDTH);
  int resize_height = cvRound(img.rows/scale);
  int resize_width = cvRound(img.cols/scale);
  Mat gray;
  Mat smallImg(resize_height, resize_width, CV_8UC1 );
  Scalar color;
  vector<Rect> filtered_objects;
  //  vector<Rect> group_bodies;

  // preprocess the input image --------------------------------------------------------------------
  cvtColor( img, gray, CV_BGR2GRAY );
  resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
  equalizeHist( smallImg, smallImg );
  
  //flip image, profile face is trained for right side so flip it so we get left side also
  Mat img_flip;
  flip(smallImg, img_flip, 1);
  

  // //---------------------------------------------------------------------------------------------------------------
   //Cascade Loop
   int valid_objects = 0;

   for( int k = 0; k < cascade_count; k++)
     {
       cascadeName =  cascades[k].cascadeName;
       if( !cascade.load( cascadeName ) ) {  cout << "using " << cascadeName  << " ERROR: Could not load" << endl; return src;}
       
       cascade.detectMultiScale( smallImg, objects,cascades[k].scale0, cascades[k].group_threshold,  cascades[k].detect_flags,  cascades[k].obj_size_threshold ); 
       if(cascades[k].tryflip == 1)
	{
	  cascade.detectMultiScale( img_flip, objects_flip,cascades[k].scale0, cascades[k].group_threshold, cascades[k].detect_flags,  cascades[k].obj_size_threshold ); 
	  
	  //add the flipped objects to objects
	  for( vector<Rect>::const_iterator r = objects_flip.begin(); r != objects_flip.end(); r++ )
	    {
	      objects.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
	    }
	}


      valid_objects = 0;
      //process the objects found for this cascade
      for( size_t i = 0; i < objects.size(); i++ )
	{
	  
	  //can get rid of these
	  Point center(cvRound((objects[i].x + objects[i].width*0.5)*scale),
		       cvRound((objects[i].y + objects[i].height*0.5)*scale));
	  int radius =  cvRound((objects[i].width + objects[i].height)*0.25*scale);
	  
	  //check valid boundaries
	  // (0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= m.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= m.rows)

	  //make sure the ROI is valid
	  if( (((objects[i].x+objects[i].width)*scale) < img.cols) && (((objects[i].y+objects[i].height)*scale) < img.rows) 
	      && (objects[i].x >= 0) && (objects[i].y >= 0))
	  {

	    Mat objectROI      = img(Rect(objects[i].x*scale, objects[i].y*scale, objects[i].width*scale, objects[i].height*scale));
	    float skin_percent = image_countSkin(objectROI);
	    Mat objectROI_gray; cvtColor(objectROI, objectROI_gray, CV_BGR2GRAY );
	    float sharpness     = MaxOfLaplacian(objectROI_gray);
	    //imshow("ROI",objectROI);
	    //waitKey();
	    
	    if( (skin_percent > cascades[k].skin_threshold)  && (sharpness > cascades[k].sharpness_threshold))
	      {
		valid_objects++;
		color = cascades[k].color;
		ellipse(img_draw, center, Size( (objects[i].width*0.5)*scale, (objects[i].height*0.5)*scale), 0, 0, 360, color, 4, 8, 0 );
		cout << "radius = " << radius 
		     << " :(x,y)=(" << center.x << ","
		     << center.y 
		     << ") skin_percent= " << skin_percent 
		     << " sharpness= " << sharpness <<endl;
		
		// cout << "cascades[k].skin_threshold = " << cascades[k].skin_threshold << "k = " << k << endl;
		
		//store all the objects so we can do grouping as a filter
		filtered_objects.push_back(objects[i]);


		//make a picture if we have a good face
                if( (cascades[k].type == FACE) && (skin_percent > 0.60) && (radius > 20) && (sharpness > 100))
		  make_picture(img,objects[i],PORTRAIT_WIDTH,PORTRAIT_HEIGHT,scale);

	      }	
	  }
	}
      cout  << cascadeName << " Objects found = " << objects.size() << " valid objects =" <<  valid_objects << endl;
    }

   img = img_draw.clone();

  //at this point we have all the detect objects from the different cascades in  vector<Rect> filtered_objects;
  //we can filter these out now
#if 0
   groupRectangles(filtered_objects, 1, 0.2);
   for( size_t i = 0; i < filtered_objects.size(); i++ )
	{

	  color = colors[0];
	  Point center(cvRound(( filtered_objects[i].x +  filtered_objects[i].width*0.5)*scale),
		       cvRound(( filtered_objects[i].y +  filtered_objects[i].height*0.5)*scale));
	  ellipse(img_group, center, Size( ( filtered_objects[i].width*0.5)*scale, ( filtered_objects[i].height*0.5)*scale), 0, 0, 360, color, 4, 8, 0 );

	}

   resize(img_group,img_group,Size(resize_width,resize_height),CV_INTER_CUBIC);
   // imshow("Group", img_group);
#endif


#if 0
  //-----------------------------------------------------------------------------------
  //http://docs.opencv.org/modules/gpu/doc/object_detection.html
  // C++: gpu::HOGDescriptor::HOGDescriptor(Size win_size=Size(64, 128), Size block_size=Size(16, 16), Size block_stride=Size(8, 8), Size cell_size=Size(8, 8), int nbins=9, double win_sigma=DEFAULT_WIN_SIGMA, double threshold_L2hys=0.2, bool gamma_correction=true, int nlevels=DEFAULT_NLEVELS)

  //Navneet Dalal and Bill Triggs. Histogram of oriented gradients for human detection. 2005.
  //http://docs.opencv.org/modules/gpu/doc/object_detection.html
  //  HOGDescriptor hog(Size(64, 128), Size(16, 16), Size(8, 8), Size(8, 8), 9, -1, 0.2, true, 64);
   HOGDescriptor hog;

   hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
  // hog.setSVMDetector(HOGDescriptor::getPeopleDetector48x96());
  //hog.setSVMDetector(HOGDescriptor::getPeopleDetector64x128());
    // hog.win_size = Size(100,200); //pixel dimensions of a person

  vector<Rect> found, found_filtered;
  // run the detector with default parameters. to get a higher hit-rate
  // (and more false alarms, respectively), decrease the hitThreshold and
  // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
  //  hog.detectMultiScale(smallImg, found, 0, Size(8,8), Size(32,32), 1.05, 0);// 2);
  hog.detectMultiScale(smallImg, found, 0, Size(8,8), Size(32,32), 1.05, 0);// 2);

  // groupRectangles(found, 1, 0.2);

  size_t i, j;
  for( i = 0; i < found.size(); i++ )
    {
      Rect r = found[i];
      for( j = 0; j < found.size(); j++ )
	if( j != i && (r & found[j]) == r)
	  break;
      if( j == found.size() )
	found_filtered.push_back(r);
    }
  for(i = 0; i < found_filtered.size(); i++ )
    {
      Rect r = found_filtered[i];
      // the HOG detector returns slightly larger rectangles than the real objects.
      // so we slightly shrink the rectangles to get a nicer output.
      r.x *= scale;     //= cvRound(r.width*0.1);
      r.width *= scale;// cvRound(r.width*0.8);
      r.y *= scale; // cvRound(r.height*0.07);
      r.height *= scale; // cvRound(r.height*0.8);
      rectangle(img, r.tl(), r.br(), cv::Scalar(255,0,0), 3);
    }
#endif

  Mat ImageResize(cvRound (img.rows/scale), cvRound(img.cols/scale), src.type() );
   resize(img,ImageResize,Size(resize_width,resize_height),CV_INTER_CUBIC);
  // resize(img,ImageResize,Size(1280,720),CV_INTER_CUBIC);
  imshow(filename, ImageResize);

  //waitKey();

  return ImageResize; //img; 

}








#if 0
for( size_t i = 0; i < objects.size(); i++ )
  {
    Point center( objects[i].x + objects[i].width*0.5, objects[i].y + objects[i].height*0.5 );
    ellipse( frame, center, Size( objects[i].width*0.5, objects[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( objects[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( objects[i].x + eyes[j].x + eyes[j].width*0.5, objects[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }
#endif


#if 0
      Mat roi_skin  = img(Rect(r->x*scale, r->y*scale, r->width*scale, r->height*scale));
      float skin_percent = image_countSkin(roi_skin);

      //      imshow("crop",roi_skin);
      cout << "skin percent = " << skin_percent << endl;
      //  waitKey(0);

      if( skin_percent > SKIN_FACE_THRESHOLD)
	{
	  //lets put out landscape and portrait crops of the objects
	  //NEED TO MAKE SURE THE DIMENSIONS ARE CORRECT
	  //check boundaries, opencv crashes because of this ....
	  int portait_width    = PORTRAIT_WIDTH;
	  int portait_height   = PORTRAIT_HEIGHT;
	  int landscape_width  = LANDSCAPE_WIDTH;
	  int landscape_height = LANDSCAPE_HEIGHT;
	  if( (r->x*scale + PORTRAIT_WIDTH) > src.cols)    portait_width    =  src.cols - r->x*scale;
	  if( (r->y*scale + PORTRAIT_HEIGHT) > src.rows)   portait_height   =  src.rows - r->y*scale;
	  if( (r->x*scale + LANDSCAPE_WIDTH) > src.cols)   landscape_width  =  src.cols - r->x*scale;
	  if( (r->y*scale + LANDSCAPE_HEIGHT) > src.rows)  landscape_height =  src.rows - r->y*scale;
	  
	  Mat roi_portrait  = img(Rect(r->x*scale, r->y*scale, portait_width  , portait_height));
	  Mat roi_landscape = img(Rect(r->x*scale, r->y*scale, landscape_width, landscape_height));
	  stringstream number;  number << crop_count;
	  string faceName_p =   OBJECTS_OUTPUT_DIR + "objects_p"+ number.str() + "_" + filename;
	  string faceName_l =   OBJECTS_OUTPUT_DIR + "objects_l"+ number.str() + "_" + filename;
	  imwrite(faceName_p, roi_portrait);
	  imwrite(faceName_l, roi_landscape);
	  crop_count++;
	}

#endif
