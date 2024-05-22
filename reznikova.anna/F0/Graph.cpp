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

void reznikova::Graph::BFS(size_t start_index, std::ostream & out) const
{
  Vertex* start_vertex = findVertex(start_index);
  if (!start_vertex) {
    throw std::logic_error("start index wasn't found");
  }
  std::queue< Vertex * > to_visit;
  std::unordered_set< size_t > visited;
  std::vector< size_t > visit_order;
  to_visit.push(start_vertex);
  visited.insert(start_vertex->getIndex());
  while (!to_visit.empty()) 
  {
    Vertex * current = to_visit.front();
    to_visit.pop();
    visit_order.push_back(current->getIndex());
    for (Vertex * neighbor : current->relatedVertices_)
    {
      if (visited.find(neighbor->getIndex()) == visited.end()) 
      {
        to_visit.push(neighbor);
        visited.insert(neighbor->getIndex());
      }
    }
  }
  for (size_t i = 0; i < visit_order.size(); ++i) 
  {
    out << visit_order[i];
    if (i < visit_order.size() - 1) 
    {
      out << " ";
    }
  }
  out << "\n";
}

void reznikova::Graph::printAdjacencyMatrix(std::ostream & out) const
{
  std::map< size_t, size_t > indexOrder;
  size_t currentIndex = 0;
  for (const auto & vertex : graph_)
  {
    indexOrder[vertex->index_] = currentIndex++;
  }
  size_t n = graph_.size();
  std::vector< std::vector< size_t > > adjacencyMatrix(n, std::vector< size_t >(n, 0));
  for (const auto & vertex : graph_)
  {
    for (const auto & neighbor : vertex->relatedVertices_)
    {
      size_t row = indexOrder[vertex->index_];
      size_t col = indexOrder[neighbor->index_];
      adjacencyMatrix[row][col] = 1;
    }
  }
  std::vector< size_t > indices;
  for (const auto & pair : indexOrder)
  {
    indices.push_back(pair.first);
  }
  std::sort(indices.begin(), indices.end());
  out << graphName_ << "\n";
  out << capacity_ << "\n";
  out << "  ";
  for (size_t idx : indices)
  {
    out << idx << " ";
  }
  out << "\n";
  for (size_t i = 0; i < n; ++i) {
    out << indices[i] << " ";
    for (size_t j = 0; j < n; ++j) {
      out << adjacencyMatrix[i][j] << " ";
    }
    out << "\n";
  }
}

reznikova::Graph reznikova::createGraphFromAdjacencyMatrix(const std::vector< size_t > & indices, 
  const std::vector< std::vector< size_t > > & matrix, const std::string & name)
{
  Graph graph(name);
  for (size_t index : indices) 
  {
    graph.addVertex(index);
  }
  size_t n = indices.size();
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (matrix[i][j] == 1 and !graph.isEdge(indices[i], indices[j]))
      {
        graph.addEdge(indices[i], indices[j]);
      }
    }
  }
  return graph;
}


