#include "image_functions.h"

#if 0
short GetSharpness(char* data, unsigned int width, unsigned int height)
{
    // assumes that your image is already in planner yuv or 8 bit greyscale
    IplImage* in = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
    IplImage* out = cvCreateImage(cvSize(width,height),IPL_DEPTH_16S,1);
    memcpy(in->imageData,data,width*height);

    // aperture size of 1 corresponds to the correct matrix
    cvLaplace(in, out, 1);

    short maxLap = -32767;
    short* imgData = (short*)out->imageData;
    for(int i =0;i<(out->imageSize/2);i++)
    {
        if(imgData[i] > maxLap) maxLap = imgData[i];
    }

    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return maxLap;
}
#endif

// OpenCV port of 'LAPM' algorithm (Nayar89)
double modifiedLaplacian(const cv::Mat& src)
{
    cv::Mat M = (Mat_<double>(3, 1) << -1, 2, -1);
    cv::Mat G = cv::getGaussianKernel(3, -1, CV_64F);

    cv::Mat Lx;
    cv::sepFilter2D(src, Lx, CV_64F, M, G);

    cv::Mat Ly;
    cv::sepFilter2D(src, Ly, CV_64F, G, M);

    cv::Mat FM = cv::abs(Lx) + cv::abs(Ly);

    double focusMeasure = cv::mean(FM).val[0];
    return focusMeasure;
}

// OpenCV port of 'LAPV' algorithm (Pech2000)
double varianceOfLaplacian(const cv::Mat& src)
{
    cv::Mat lap;
    cv::Laplacian(src, lap, CV_64F);

    cv::Scalar mu, sigma;
    cv::meanStdDev(lap, mu, sigma);

    double focusMeasure = sigma.val[0]*sigma.val[0];
    return focusMeasure;
}


double MaxOfLaplacian(const cv::Mat& src)
{
    cv::Mat lap;
    cv::Laplacian(src, lap, CV_64F);

    double minVal; 
    double maxVal; 
    Point minLoc; 
    Point maxLoc;
    
    minMaxLoc( lap, &minVal, &maxVal, &minLoc, &maxLoc );

    //imshow("sharpness", lap);
    //  waitKey();

    return maxVal;
}



// OpenCV port of 'TENG' algorithm (Krotkov86)
double tenengrad(const cv::Mat& src, int ksize)
{
    cv::Mat Gx, Gy;
    cv::Sobel(src, Gx, CV_64F, 1, 0, ksize);
    cv::Sobel(src, Gy, CV_64F, 0, 1, ksize);

    cv::Mat FM = Gx.mul(Gx) + Gy.mul(Gy);

    double focusMeasure = cv::mean(FM).val[0];
    return focusMeasure;
}

// OpenCV port of 'GLVN' algorithm (Santos97)
double normalizedGraylevelVariance(const cv::Mat& src)
{
    cv::Scalar mu, sigma;
    cv::meanStdDev(src, mu, sigma);

    double focusMeasure = (sigma.val[0]*sigma.val[0]) / mu.val[0];
    return focusMeasure;
}
