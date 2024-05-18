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
    unsigned long long count = std::stoll(command);  //create< count, graphname >
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
    graphList[parameter] = graph;
  }
  else
  {
    graphsList[parameter]; //create< graphname >
  }
}
