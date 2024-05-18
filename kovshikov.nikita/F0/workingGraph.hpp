#ifndef WORKINGGRAPH_HPP
#define WORKINGGRAPH_HPP
#include "orientedGraph.hpp"
#include <iostream>

namespace kovshikov
{
  bool isDigit(char ch);
  std::string getGraphname(std::pair< std::string, Graph > element);

  void add(Graph& graph, std::istream& is);
  void connect(Graph& graph, std::istream& is);
  void getDouble(Graph& graph, std::istream& is);
  void deleteElement(Graph& graph, std::istream& is);
}

#endif
