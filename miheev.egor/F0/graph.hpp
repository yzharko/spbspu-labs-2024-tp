#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <unordered_map>

namespace miheev
{
  class Edge;
  class Node
  {
  public:
    Node(int name);
    void addEdge();
  private:
    int name_;
    std::unordered_set< Edge > edges;
    std::unordered_map< Edge, Node > backLinks;
  };

  class Edge
  {
  public:
    Edge(const Node*, size_t weight = 1); // TODO: перегрузить для обыного указателя
  private:
    size_t weight_;
    const Node* dest_;
  };
}

#endif