#include "WorkSpace.hpp"
#include <iterator>

bool reznikova::GraphList::isGraphInList(std::string graphName) const
{
  auto graph = std::find_if(
    graphList_.begin(),
    graphList_.end(),
    [&] (WorkObject * graphToCmp)
    {
     return graphToCmp->graph_.getGraphName() == graphName;
    });
  return graph != graphList_.end();
}

void reznikova::WorkObject::resetFlag()
{
  isActive_ = false;
}

void reznikova::GraphList::addToList(reznikova::Graph graph)
{
  if (isGraphInList(graph.getGraphName()))
  {
    throw std::logic_error("this graph is already exists\n");
  }
  resetActiveFlags();
  graphList_.emplace_back(new WorkObject(graph));
}

void reznikova::GraphList::resetActiveFlags()
{
  std::vector< WorkObject * > temp;
  std::transform(
    graphList_.begin(),
    graphList_.end(),
    std::back_inserter(temp),
    [](WorkObject * obj)
    {
     obj->resetFlag();
     return obj;
    });
  graphList_ = temp;
}

reznikova::WorkObject * reznikova::GraphList::findGraphByName(std::string graphName) const
{
  auto graph = std::find_if(
    graphList_.begin(),
    graphList_.end(),
    [&] (WorkObject * objToCmp)
    {
     return objToCmp->graph_.getGraphName() == graphName;
    });
  return graph == graphList_.end() ? nullptr : (*graph);
}

reznikova::WorkObject * reznikova::GraphList::getActiveGraph() const
{
  if (graphList_.empty())
  {
    throw std::logic_error("You did not add any graph\n");
  }
  auto graph = std::find_if(
    graphList_.begin(),
    graphList_.end(),
    [] (WorkObject * objToCmp)
    {
     return objToCmp->isActive_ == true;
    });
  return *graph;
}

