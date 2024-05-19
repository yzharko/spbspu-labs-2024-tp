#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP
#include <map>

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
	Graph findActiveWorkspace()
	{
	  for (auto it = graphList.begin(); it != graphList.end(); ++it)
	  {
		if (it->second.activityFlag)
		{
		  return it->second.actualGraph;
		}
	  }
	}
  };
}

#endif
