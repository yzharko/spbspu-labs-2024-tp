#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "createGraph.hpp"

bool kovshikov::isDigit(char ch)
{
  return std::isdigit(ch);
}

void kovshikov::createGraph(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    std::cout << "WTF\n";
    unsigned long long count = std::stoll(parameter);  //create< count, graphname >
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    for(size_t i = 1; i <= count; i++)
    {
      for(size_t j = 1; j <= count; j++)
      {
        if(i != j)
        {
          graph.createEdge(i, j, 1);
        }
      }
    }
    std::string graphname;
    is >> graphname;
    graphsList[graphname] = graph;
  }
  else
  {
    graphsList[parameter]; //create< graphname >
  }
}
