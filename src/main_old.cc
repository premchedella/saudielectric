#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


const int LOOP_NUM = 10;


struct SURFDetector
{
  Ptr<Feature2D> surf;
  SURFDetector(double hessian = 800.0)
  {
    surf = SURF::create(hessian);
  }
  template<class T>
  void operator()(const T& in, const T& mask, std::vector<cv::KeyPoint>& pts,
      T& descriptors, bool useProvided = false)
  {
    surf->detectAndCompute(in, mask, pts, descriptors, useProvided);
  }
};



struct SIFTDetector
{
  Ptr<Feature2D> surf;
  SIFTDetector()
  {
    surf = SIFT::create();
  }
  template<class T>
  void operator()(const T& in, const T& mask, std::vector<cv::KeyPoint>& pts,
    T& descriptors, bool useProvided = false)
  {
    surf->detectAndCompute(in, mask, pts, descriptors, useProvided);
  }
};



int main(int argc, char** argv)
{
  cout << "Welcome to MVE SFM." << endl;

  //cout << "Number of Arguments = " << argc << endl;

  string image_file_name = argv[1];

  cout << "Image File = " << image_file_name.c_str() << endl;

  //Load as grayscale

  /*cv::IMREAD_COLOR : Loads a color image.Any transparency of image will be
      neglected.It is the default flag.
    cv::IMREAD_GRAYSCALE : Loads image in grayscale mode
    cv::IMREAD_UNCHANGED : Loads image as such including alpha channel 
  */

  const cv::Mat image_data = cv::imread(image_file_name, cv::IMREAD_GRAYSCALE);
  cout << "The size of the image Width = " << image_data.cols
      << " Height = " << image_data.rows <<endl; 
  /*cv::SiftFeatureDetector detector;
  std::vector<cv::KeyPoint> keypoints;
  detector.detect(image_data, keypoints);*/

  /*cv::Ptr<Feature2D> f2d = cv::xfeatures2d::SIFT::create();
  std::vector<KeyPoint> keypoints_1, keypoints_2;
  f2d->detect(image_data, keypoints_1);*/

  SURFDetector surf;
  vector<KeyPoint> surf_keypoints;  
  UMat image1;
  image_data.copyTo(image1);

  if (image1.empty()) {
    cout << "Couldn't load " << image_file_name.c_str() << endl;    
    return EXIT_FAILURE;
  }

  UMat su_descriptors;
  Mat surf_descriptors = su_descriptors.getMat(ACCESS_RW);
    
  surf(image1.getMat(ACCESS_READ), Mat(), surf_keypoints, surf_descriptors);
  
  
  cout << "SURF " << surf_keypoints.size() << " keypoints on first image"
      << endl;


  SIFTDetector sift;
  vector<KeyPoint> sift_keypoints;
  

  UMat sif_descriptors;
  Mat sift_descriptors = sif_descriptors.getMat(ACCESS_RW);

  sift(image1.getMat(ACCESS_READ), Mat(), sift_keypoints, sift_descriptors);


  cout << "SIFT " << sift_keypoints.size() << " keypoints on first image"
      << endl;

  vector<Point2f> surf_points;
  for (unsigned int counter = 0; counter < surf_keypoints.size(); counter++) {
    surf_points.push_back(surf_keypoints.at(counter).pt);
  }

  vector<Point2f> sift_points;
  for (unsigned int counter = 0; counter < sift_keypoints.size(); counter++) {
    sift_points.push_back(sift_keypoints.at(counter).pt);
  }
  unsigned int max_key_points = 0;
  vector<Point2f> max_points;
  vector<Point2f> min_points;

  if (surf_keypoints.size() > sift_keypoints.size()) {
    max_key_points = surf_keypoints.size();
    min_points = surf_points;
  } else {
    max_key_points = sift_keypoints.size();
    max_points = sift_points;
  }

  cout << "Max Key Points  = " << max_key_points << endl;
  unsigned int matches = 0;
  for (unsigned int counter = 0; counter < max_key_points; counter++) {
    Point2f point = max_points.at(counter);
    vector<Point2f>::iterator it;

    it = find(min_points.begin(), min_points.end(), point);
    if (it != min_points.end()) {
      matches++;
    }    
  }

  cout << "Number of Matches = " << matches << endl;
  return 0;
}

