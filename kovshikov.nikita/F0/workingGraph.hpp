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
  void getWeight(Graph& graph, std::istream& is);
  void getDegree(Graph& graph, std::istream& is);
  void getOwn(Graph& graph, std::istream& is);
  void change(Graph& graph, std::istream& is);

  void getCountVertex(Graph& graph, std::ostream& out);
  void outEdge(Graph& graph, std::ostream& out);
  void outMax(Graph& graph, std::ostream& out);
  void outName(std::string key, std::ostream& out);
}

#endif
