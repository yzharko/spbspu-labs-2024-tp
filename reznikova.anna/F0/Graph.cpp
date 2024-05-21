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

void reznikova::Graph::addVertex(size_t index)
{
  if (isVertex(index))
  {
    throw std::logic_error("this vertex is already exist\n");
  }
  graph_.emplace_back(new Vertex(index));
  capacity_++;
}

void reznikova::Graph::addEdge(size_t first_index, size_t second_index)
{
  if (!isVertex(first_index) or !isVertex(second_index))
  {
    throw std::logic_error("can't add edge between vertices which does not exist\n");
  }
  else if (isEdge(first_index, second_index))
  {
    throw std::logic_error("this edge is already exist\n");
  }
  Vertex * first_vertex = findVertex(first_index);
  Vertex * second_vertex = findVertex(second_index);
  first_vertex->add(second_vertex);
  second_vertex->add(first_vertex);
}

void reznikova::Graph::removeVertex(size_t index)
{
  if (!isVertex(index))
  {
    throw std::logic_error("can't remove vertex which does not exist\n");
  }
  Vertex * target = findVertex(index);
  for (auto vertex: graph_) 
  {
    if (vertex != target) 
    {
      vertex->remove(target);
    }
  }
  graph_.erase(std::remove(graph_.begin(), graph_.end(), target));
  capacity_--;
}

void reznikova::Graph::removeEdge(size_t first_index, size_t second_index)
{
  if (!isVertex(first_index) or !isVertex(second_index))
  {
    throw std::logic_error("can't delete edge between vertices which does not exist\n");
  }
  else if (!findVertex(first_index)->isRelated(second_index))
  {
    throw std::logic_error("this edge is does not exist\n");
  }
  Vertex * first_vertex = findVertex(first_index);
  Vertex * second_vertex = findVertex(second_index);
  first_vertex->remove(second_vertex);
  second_vertex->remove(first_vertex);
}
