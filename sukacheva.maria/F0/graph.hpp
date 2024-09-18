#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include <map>
#include <vector>

namespace sukacheva
{
  class Graph
  {
  public:
    std::string GraphName;
    std::map< size_t, std::string > VertexesList;

    Graph() = default;
    Graph(std::string GraphName_);
    Graph(const Graph& graph) = default;
    Graph& operator=(const Graph& graph) = default;
    ~Graph() = default;

    void addVertex(std::string& name);
    void addEdge(std::string& start, std::string& end, size_t weight);
    void deleteVertex(std::string name);
    void deleteEdge(std::string start, std::string end);
    size_t capacity();
    void clear();
    size_t getVertexIndex(std::string& name);
    std::pair< std::map< size_t, size_t >, std::map< size_t, size_t > > dijkstraDistances(std::string name);
    std::vector< std::string > dijkstraPath(const std::map< size_t, size_t >& predecessors, std::string start, std::string end);
    std::vector< std::vector< size_t > > weightTable();
    bool isVertexExist(std::string& name);
    bool isEdgeExist(std::string& start, std::string& end);
  private:
    std::map< size_t, std::map< size_t, size_t > > AdjacencyList;
  };
  std::istream& operator>>(std::istream& in, Graph& applicant);
}

#endif
