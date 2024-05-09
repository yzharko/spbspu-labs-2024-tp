#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <map>
#include <forward_list>
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
    void addEdge(int lnode, int rnode, size_t weight = 2);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    void navigate(); // как плейсхолдер для функции

    std::ostream& printNodes(std::ostream&);
    std::ostream& printAllEdges(std::ostream&);

  private:
    std::string name_;
    std::string filename_;
    std::map< int, Node > nodes_;

    friend std::istream& operator>>(std::istream&, const Graph&);
    struct Printer;
    struct Dextra;
  };

  struct Graph::Printer
  {
    std::ostream& printUniqueEdges(const Node&, std::ostream&);
    std::unordered_set< int > visitedNodes;
    bool somethingPrinted;
  };

  struct Graph::Dextra
  {
    Dextra(const Graph&);

    void operator()(int begin, int end);

    void calcMinTimeToEach();
    int getNodeWithMinimumTimeToIt();
    std::forward_list< int > findShortestPath(int finish, int start);

    void updateNodeState(int node, size_t timeToNode, int parrentNode = -1);

    const Graph& graph;
    std::unordered_set< int > unprocessedNodes;
    std::map <int, int> nodesParrents; // first - node, second - it' pair
    std::map< int, size_t > timeToNodes;
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