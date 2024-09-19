#ifndef Vertex_hpp
#define Vertex_hpp
#include <iomanip>
#include <vector>

namespace reznikova
{
  struct Vertex
  {
    explicit Vertex(size_t index): index_(index) {};
    bool isRelated(size_t vertex) const;
    void add(Vertex* vertex);
    void remove(Vertex* vertex);
    std::size_t getIndex();
    size_t index_;
    std::vector< Vertex * > relatedVertices_;
  };
}

#endif
