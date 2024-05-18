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

void kovshikov::createLonely(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  std::string graphname; //lonely< name > < count >
  is >> graphname;
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    unsigned long long count = std::stoll(parameter);
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    graphsList[graphname] = graph;
  }
  else
  {
    throw std::logic_error("This is not number");
  }
}

void kovshikov::deleteGraph(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  //delete< graphname >
  std::string key;
  is >> key;
  if(graphsList.find(key) == graphsList.end())
  {
    throw std::logic_error("This graph is not there");
  }
  else
  {
    graphsList.erase(key);
  }
}
