#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <map>
#include <forward_list>
#include <vector>
#include <ios>

namespace miheev
{
  class Graph
  {
  private:
    struct Node;
    struct Edge;

  public:
    Graph() = default;

    const std::string& getName() const noexcept;
    void setName(const std::string& name);

    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight = 1);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    std::forward_list< const Node& > navigate(); // если существует возможность, не допускать такого копирования

    std::ostream& printNodes(std::ostream&);
    std::ostream& printEdges(std::ostream&);

  private:
    std::string name_;
    std::string filename_;
    std::map< int, Node > nodes_;
    friend std::istream& operator>>(std::istream&, const Graph&);
  };

  struct Graph::Edge
  {
    Node* dest;
    size_t weight;
    struct HashFunction;
    bool operator==(const Edge&) const;
  };

  struct Graph::Edge::HashFunction
  {
    size_t operator()(const Edge& rhs) const;
  };

  struct Graph::Node
  {
    int name;
    std::unordered_set< Edge, Edge::HashFunction > edges;
    std::map< int, Edge > backLinks;
  };
  std::istream& operator>>(std::istream&, const Graph&);

}

#endif