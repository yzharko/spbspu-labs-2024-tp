#include "Vertex.hpp"
#include <algorithm>

bool reznikova::Vertex::isRelated(size_t vertex) const
{
  auto relatedVertex = std::find_if(
    relatedVertices_.begin(),
    relatedVertices_.end(),
    [&] (Vertex * vertexToCmp)
    {
      return vertexToCmp->index_ == vertex;
    });
  return relatedVertex != relatedVertices_.end();
}

void reznikova::Vertex::add(Vertex * vertex)
{
  if (isRelated(vertex->index_)) {
    throw std::logic_error("can't add edge which exists\n");
  }
  relatedVertices_.push_back(vertex);
}

void reznikova::Vertex::remove(Vertex * vertex)
{
  relatedVertices_.erase(
    std::remove(relatedVertices_.begin(), relatedVertices_.end(), vertex),
    relatedVertices_.end());
}

std::size_t reznikova::Vertex::getIndex()
{
  return index_;
}
