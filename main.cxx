#include <set>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <string>
#include <iostream>
#include "Build.h"
#include "Feature.h"

bool init_system( std::string, std::set< Building >& );
void save_images( std::set< Building > );
void save_feature_image( std::set< Building > );
Building seek( std::string, std::set< Building > );

int main()
{
  std::string command;
  std::set< Building > buildings;
  Building the_sought;
  bool init = false;

  do
  {
    std::cout << "$ ";
    std::getline( std::cin, command );
    std::istringstream tokenize( command );
    std::string token;
    std::getline( tokenize, token, ' ' );
    if( token == "init" && !init )
    {
      std::getline( tokenize, token, ' ' );
      init = init_system( token, buildings );
      if(init)
        std::cout << "System Initialized" << std::endl;
      else
        std::cerr << "Failed Initialization" << std::endl;
        std::cout << std::endl;
    }
    else if( token == "seek" && init )
    {
      std::getline( tokenize, token, ' ' );
      the_sought = seek( token, buildings );
      if( the_sought != Building() )
      {
        std::cout << "the Building sought is: " << the_sought.getName() << std::endl;
        cv::imshow("The Sought", (the_sought.getFeatures()).front().getImage());
        cv::waitKey(0);
      }
      else
        std::cout << "Building not sought." << std::endl;
      std::cout <<  std::endl;
    }
    else if( token == "save_images" && init )
    {
      save_images( buildings );
      std::cout << std::endl;
    }
    else if( token == "save_feature" && init )
    {
      save_feature_image( buildings );
      std::cout << std::endl;
    }
    else if( token != "exit" )
    {
      std::cerr << "Command not found" << std::endl << std::endl;
    }
  }while( command != "exit" );

  return 0;
}

bool init_system( std::string file_name, std::set<Building>& buildings )
{
  std::string linea, name;
  std::ifstream init_file( file_name );
  Building aux_build;
  int number_build, number_image;

  if( init_file.is_open() )
  {
    init_file >> linea;
    number_build = std::atoi( linea.c_str() );
    while( number_build > 0 )
    {
      init_file >> name;
      aux_build = Building( name );
      init_file >> linea;
      number_image = std::atoi( linea.c_str() );
      while( number_image > 0 )
      {
        init_file >> linea;
        aux_build.addFeature( linea );
        number_image--;
      }
      buildings.insert( aux_build );
      std::cout << aux_build.getName() << " added" << std::endl;
      number_build--;
    }
    return true;
  }
  else
  {
    std::cerr << "File doesn't exist." << std::endl;
    return false;
  }
}

void save_images( std::set< Building > buildings )
{
  std::set<Building>::iterator it = buildings.begin();
  for(; it != buildings.end(); it++)
  {
    Building build = (*it);
    build.saveImages();
    std::cout << build.getName() << " saved" << std::endl;
  }
}

void save_feature_image( std::set< Building > buildings )
{
  std::set<Building>::iterator it = buildings.begin();
  for(; it != buildings.end(); it++)
  {
    Building build = (*it);
    build.saveImagesFeature();
    std::cout << build.getName() << " Features saved" << std::endl;
  }
}

Building seek( std::string image_name, std::set< Building > buildings )
{
  Building build;
  bool sought = false;
  Feature the_sought( image_name );

  if( the_sought.getImage().data )
  {
    std::set<Building>::iterator it = buildings.begin();
    for(; it != buildings.end() && !sought; it++)
    {
      build = (*it);
      std::cout << "compare with " << build.getName() << std::endl;
      if( build.itsMe( the_sought ) )
        sought = true;
    }
    if(sought)
      return build;
    else
      return Building();
  }
  else
    return Building();
}
