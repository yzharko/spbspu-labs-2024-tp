#ifndef Graph_hpp
#define Graph_hpp
#include <vector>
#include <string>
#include "Vertex.hpp"

namespace reznikova
{
  struct Graph
  {
    Graph(std::string name);
    std::string getGraphName() const;
    size_t getCapacity() const;
    Vertex * findVertex(size_t index) const;
    bool isVertex(size_t index) const;
    bool isEdge(size_t first_index, size_t second_index) const;
    void addVertex(size_t index);
    void addEdge(std::size_t first_index, size_t second_index);
    void removeVertex(size_t index);
    void removeEdge(size_t first_index, size_t second_index);
    void BFS(size_t start_index, std::ostream & out) const;
    void printAdjacencyMatrix(std::ostream & out) const;
  private:
    std::vector< Vertex * > graph_;
    std::string graphName_;
    size_t capacity_;
  };
Graph createGraphFromAdjacencyMatrix(const std::vector< size_t > & indices, const std::vector< std::vector< size_t > > & matrix,
const std::string & name);
}

#endif
