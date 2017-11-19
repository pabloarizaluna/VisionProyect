#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <list>
#include <vector>
#include <opencv2/opencv.hpp>

class Feature
{
private:
  cv::Mat image;
  std::vector < cv::KeyPoint > keypoints;

public:
  Feature();
  Feature( std::string );
  cv::Mat getImage();
  std::vector< cv::KeyPoint > getKeyPoints();
  void saveImage( std::string );
};

#endif
