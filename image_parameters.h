#ifndef IMAGE_PARAMETERS_H
#define IMAGE_PARAMETERS_H


#define FILTER_OBJS

#define DPI 300    //need 300 dots per inch for good quality printing

#define OPENCV_DATA_DIR string("/home/kcoopman/Nagler/XML_Cascades/")
#define FACES_OUTPUT_DIR string("./faces/")
#define RESIZE_OUTPUT_DIR string("./resize/")
#define HISTO_OUTPUT_DIR string("./histo/")
#define SKIN_OUTPUT_DIR string("./skin/")

//skin thresholds
//we should look at the laplacian max of the original image and go from there ....
//can be a factor of 2 difference between cameras

#ifdef FILTER_OBJS
#define SKIN_FACE_THRESHOLD            0.2
#define SKIN_FACE_FEATURE_THRESHOLD    0.5
#define SHARPNESS_FACE_THRESHOLD       50
#else
#define SKIN_FACE_THRESHOLD            0.0
#define SKIN_FACE_FEATURE_THRESHOLD    0.0
#define SHARPNESS_FACE_THRESHOLD       0
#endif

//cropping dimesions for faces
#define PORTRAIT_WIDTH  (2*DPI)
#define PORTRAIT_HEIGHT (3*DPI)
#define LANDSCAPE_WIDTH  (3*DPI)
#define LANDSCAPE_HEIGHT (2*DPI)

#define FACE_DETECT_RESIZE_WIDTH  (720)


//-------------------------------------------------------------
//colors for drawing
#define ORANGE     CV_RGB(255,128,0)
#define BLUE       CV_RGB(0,0,255)
#define GREEN      CV_RGB(0,255,0)
#define RED        CV_RGB(255,0,0)
#define YELLOW     CV_RGB(255,255,0)
#define MAGENTA    CV_RGB(255,0,255)
#define TEAL       CV_RGB(0,255,255)
#define LIGHT_BLUE CV_RGB(0,128,255)



#endif
