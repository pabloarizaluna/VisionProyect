#ifndef __BUILD_H__
#define __BUILD_H__

#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <opencv2/opencv.hpp>
#include "Feature.h"

class Building
{
private:
  std::string name;
  std::list< Feature > features;

public:
  Building();
  Building( std::string );
  std::string getName();
  std::list< Feature > getFeatures();
  bool addFeature( std::string );
  void saveImages();
  bool itsMe( cv::Mat input );

  friend bool operator>( const Building& left, const Building& right );
	friend bool operator<( const Building& left, const Building& right );
	friend bool operator==( const Building& left, const Building& right );
	friend bool operator!=( const Building& left, const Building& right );
};

#endif
