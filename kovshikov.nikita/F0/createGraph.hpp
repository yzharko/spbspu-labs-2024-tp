#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HP
#include "orientedGraph.hpp"

namespace kovshikov
{
  void createGraph(std::map< std::string, Graph >& graphsList, std::istream& is);
  bool isDigit(char ch);
}

#endif
