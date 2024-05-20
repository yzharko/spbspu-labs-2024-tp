#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP
#include <map>
#include <string>
#include <stdexcept>

namespace sukacheva
{
  struct Workspace
  {
    Workspace(Graph actualGraph_): actualGraph(actualGraph_), activityFlag(true) {}
    ~Workspace() = default;
    Graph actualGraph;
    bool activityFlag;
  };

  struct GraphList
  {
    GraphList() = default;
    ~GraphList() = default;
    std::map< std::string, Workspace > graphList;
    Graph& findActiveWorkspace()
    {
      auto it = std::find_if(
        graphList.begin(),
        graphList.end(),
        [](std::pair< std::string, Workspace > pair) { return pair.second.activityFlag; }
      );

      if (it != graphList.end())
      {
        return it->second.actualGraph;
      }
      else
      {
        throw std::logic_error("No active workspace found");
      }
    }
    Graph& findGraphName(std::string& name)
    {
      auto it = std::find_if(
        graphList.begin(),
        graphList.end(),
        [name](std::pair< std::string, Workspace > pair) { return pair.first == name; }
      );

      if (it != graphList.end())
      {
        return it->second.actualGraph;
      }
      else
      {
        throw std::logic_error("Graph with the specified name not found");
      }
    }
  };
}

#endif
