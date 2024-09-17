#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP
#include <map>
#include <string>
#include "graph.hpp"

namespace sukacheva
{
  struct Workspace
  {
    Workspace(Graph actualGraph_): actualGraph(actualGraph_), activityFlag(false) {}
    ~Workspace() = default;
    Graph actualGraph;
    bool activityFlag;
  };

  struct GraphList
  {
    GraphList() = default;
    ~GraphList() = default;
    std::map< std::string, Workspace > graphList;
    Graph& findActiveWorkspace();
    Graph& findGraphName(std::string& name);
    Graph& switchActualGraph(std::string& name);
  };
}

#endif
