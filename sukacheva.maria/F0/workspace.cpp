#include "workspace.hpp"
#include <stdexcept>

namespace sukacheva
{
  Graph& sukacheva::GraphList::findActiveWorkspace()
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
      throw std::logic_error("No active workspace found.\n");
    }
  }

  Graph& sukacheva::GraphList::findGraphName(std::string& name)
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
      throw std::logic_error("Graph with the specified name not found.\n");
    }
  }

  Graph& sukacheva::GraphList::switchActualGraph(std::string& name)
  {
    auto it = std::find_if(
      graphList.begin(),
      graphList.end(),
      [](std::pair< std::string, Workspace > pair) { return pair.second.activityFlag; }
    );

    if (it != graphList.end())
    {
      it->second.activityFlag = false;
    }
    auto itNew = std::find_if(
      graphList.begin(),
      graphList.end(),
      [name](std::pair< std::string, Workspace > pair) { return pair.first == name; }
    );

    if (itNew != graphList.end())
    {
      itNew->second.activityFlag = true;
      return itNew->second.actualGraph;
    }
    else
    {
      throw std::logic_error("Graph with the specified name not found.\n");
    }
  }
}
