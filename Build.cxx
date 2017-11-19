#include "Build.h"

Building::Building()
{

}
Building::Building( std::string name )
{
  this->name = name;
  this->features = std::list< Feature >();
}

std::string Building::getName()
{
  return this->name;
}

std::list< Feature > Building::getFeatures()
{
  return this->features;
}

bool Building::addFeature( std::string image_name )
{
  Feature *feature = new Feature(image_name);
  (this->features).push_back( *feature );
}

bool Building::itsMe( cv::Mat input )
{
  //TODO compare the inputs with this building
}

void Building::saveImages()
{
  int i = 0;
  std::list< Feature >::iterator it = (this->features).begin();
  for(; it != (this->features).end(); it++ )
  {
    (*it).saveImage(this->name + "_" + std::to_string(i));
    i++;
  }
}


bool operator>( const Building& left, const Building& right )
{
  return left.name > right.name;
}

bool operator<( const Building& left, const Building& right )
{
  return left.name < right.name;
}

bool operator==( const Building& left, const Building& right )
{
  return left.name == right.name;
}

bool operator!=( const Building& left, const Building& right )
{
  return left.name != right.name;
}
