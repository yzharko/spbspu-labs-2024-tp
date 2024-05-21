#include "Graph.hpp"
#include <queue>
#include <map>
#include <unordered_set>

reznikova::Graph::Graph(std::string name):
graphName_(name),
capacity_(0)
{}

std::string reznikova::Graph::getGraphName() const
{
  return graphName_;
}

size_t reznikova::Graph::getCapacity() const
{
  return capacity_;
}

reznikova::Vertex * reznikova::Graph::findVertex(size_t index) const
{
  auto vertex = std::find_if(
    graph_.begin(),
    graph_.end(),
    [&] (Vertex * vertexToCmp)
    {
     return vertexToCmp->getIndex() == index;
    });
  return vertex == graph_.end() ? nullptr : (*vertex);
}

bool reznikova::Graph::isVertex(std::size_t index) const
{
  auto vertex = std::find_if(
    graph_.begin(),
    graph_.end(),
    [&] (Vertex * vertexToCmp)
    {
     return vertexToCmp->getIndex() == index;
    });
  return vertex != graph_.end();
}

bool reznikova::Graph::isEdge(size_t first_index, size_t second_index) const
{
  if (!isVertex(first_index) or !isVertex(second_index))
  {
    throw std::logic_error("no such vertices\n");
  }
  return findVertex(first_index)->isRelated(second_index);
}
