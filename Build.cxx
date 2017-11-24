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
  Feature feature = Feature(image_name);
  (this->features).push_back( feature );
}

bool Building::itsMe( Feature input )
{
  int sum = 0;
  bool sought = false;
  float corr;
  std::list< Feature >::iterator it = (this->features).begin();
  for(; it != (this->features).end() && !sought; it++ )
  {
    std::vector<float> result = (*it).equal( input );
    if( result[0] > 0.75)
      sum++;
    if( result[1] >= 0.9 )
    {
      sought = true;
      corr = result[1];
    }
  }
  std::cout << "sum: " << sum << " size: " << (this->features).size() / 2 << std::endl;
  if( (sum > (this->features).size() / 2) || corr >= 0.9 )
    sought = true;
  return sought;
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

void Building::saveImagesFeature()
{
  int i = 0;
  std::list< Feature >::iterator it = (this->features).begin();
  for(; it != (this->features).end(); it++ )
  {
    (*it).saveImageFeature(this->name + "_feature_" + std::to_string(i));
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
