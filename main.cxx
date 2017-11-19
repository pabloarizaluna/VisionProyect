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

int main()
{
  std::string command;
  std::set< Building > buildings;
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
    }
    else if( token == "find" )
    {

    }
    else if( token == "save_images")
    {
      save_images(buildings);
    }
    else if( token != "exit" )
    {
      std::cerr << "Command not found" << std::endl;
    }
  }while(command != "exit");

  return 0;
}

bool init_system( std::string file_name, std::set<Building>& buildings )
{
  std::string linea, name;
  std::ifstream init_file( file_name );
  Building *aux_build;
  int number_build, number_image;

  if( init_file.is_open() )
  {
    std::cout << "hola" << std::endl;
    init_file >> linea;
    number_build = std::atoi( linea.c_str() );
    std::cout << linea << " " << number_build << std::endl;
    while( number_build > 0 )
    {
      init_file >> name;
      aux_build = new Building( name );
      init_file >> linea;
      number_image = std::atoi( linea.c_str() );
      std::cout << number_image << std::endl;
      while( number_image > 0 )
      {
        init_file >> linea;
        aux_build->addFeature( linea );
        number_image--;
      }
      buildings.insert( *aux_build );
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
    std::cout << "size: " << (build.getFeatures()).size() << std::endl;
  }
}
