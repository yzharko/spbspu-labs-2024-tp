#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HP
#include "orientedGraph.hpp"
#include "workingGraph.hpp"

namespace kovshikov
{
  void createGraph(std::map< std::string, Graph >& graphsList, std::istream& is);
  void createLonely(std::map< std::string, Graph >& graphsList, std::istream& is);
  void deleteGraph(std::map< std::string, Graph >& graphsList, std::istream& is);
  void workWith(std::map< std::string, Graph >& graphsList, std::istream& is);

  void outputGraphs(const std::map< std::string, Graph >& graphsList, std::ostream& out);
  void outputVertexes(const std::map< std::string, Graph >& graphsList, std::ostream& out);
}

#endif
