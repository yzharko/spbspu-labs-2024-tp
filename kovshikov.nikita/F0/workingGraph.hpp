#ifndef WORKINGGRAPH_HPP
#define WORKINGGRAPH_HPP
#include "orientedGraph.hpp"
#include <iostream>

namespace kovshikov
{
   bool isDigit(char ch);

  void add(Graph& graph, std::istream& is);
  std::string getGraphname(std::pair< std::string, Graph > element);
}

#endif
