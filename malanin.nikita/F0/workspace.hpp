#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "graph.hpp"
#include <vector>

namespace malanin
{
  struct Workspace
  {
    std::map< std::string, Graph > graphs;
    Graph current;
    bool isActive;
  };
}

#endif
