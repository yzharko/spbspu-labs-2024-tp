#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "createGraph.hpp"
#include "supportive.hpp"


void kovshikov::createGraph(const std::map< std::string, Graph >& graphsList, std::istream& is);
{
  std::string parameter;
  is >> parameter;
  if(std::all_of(command.begin(), command.end(), isDigit) == true)
  {
    
  }
  else
  {
    graphsList[parameter];
  }
}
