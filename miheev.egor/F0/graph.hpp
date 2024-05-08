#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <map>
#include <forward_list>
#include <vector>
#include <ios>

namespace miheev
{
  class Node;

  class Edge
  {
  public:
    Edge();
    Edge(Node*, size_t weight = 1);

    bool operator==(const Edge&) const;

    struct HashFunction;

  private:
    // friend class Node;
    size_t weight_;
    Node* dest_; // TODO: возможно указатель следует сделать константным;
  };


  struct Edge::HashFunction
  {
    size_t operator()(const Edge&) const;
  };

  class Node
  {
  public:
    Node(int name);
    ~Node() = default;

    void addEdge(const Edge&);
    void rmEdge(const Edge&);

    void addBacklink(const Edge&);
    void rmBacklink(const Edge&);

    int name() const noexcept;

  private:
    friend class Graph;
    int name_;
    std::unordered_set< Edge, Edge::HashFunction > edges_;
    std::map< int, Edge > backLinks_;
  };

  class Graph
  {
  public:
    Graph() = default;
    const std::string& getName() const noexcept;
    void setName(const std::string& name);
    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);
    std::forward_list< Node > navigate(); // если существует возможность, не допускать такого копирования
    void printEdges(std::ostream&);
    void printNodes(std::ostream&);
  private:
    std::string name_;
    std::map< int, Node > nodes_;
    friend std::istream& operator>>(std::istream&, const Graph&);
  };
  std::istream& operator>>(std::istream&, const Graph&);

}

#endif