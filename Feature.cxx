#include "Feature.h"

Feature::Feature()
{
  this->image = cv::Mat();
  this->keypoints = std::vector< cv::KeyPoint >();
}

Feature::Feature( std::string image_name )
{
  cv::Mat image, aux, image_gray;
  image = cv::imread(image_name, 1);
  if(!image.data)
  {
    std::cout << "Image Error." << std::endl;
  }

  double fx, fy;
  fx = 512.0/image.cols;
  fy = 512.0/image.rows;
  aux = cv::Mat(512, 512, image.type());
  cv::resize(image, aux, cv::Size(), fx, fy);
  this->image = aux.clone();

  cv::cvtColor(aux, image_gray, cv::COLOR_RGB2GRAY);
  cv::medianBlur(image_gray, image_gray, 3);
  cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(25);
  fast->detect(image_gray, this->keypoints);
  cv::imwrite("prueba.png", this->image);
}

cv::Mat Feature::getImage()
{
  return (this->image).clone();
}

std::vector< cv::KeyPoint > Feature::getKeyPoints()
{
  return this->keypoints;
}

void Feature::saveImage( std::string name )
{
  cv::imwrite(name + ".png", this->image);
}
