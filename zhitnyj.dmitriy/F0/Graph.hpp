#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <string>

struct Graph {
  std::map< std::string, std::map< std::string, int > > adjList;
  std::map< std::string, int > distances;
  std::map< std::string, std::string > predecessors;
};

#endif
