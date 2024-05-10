#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <iostream>

namespace miheev
{
  class Graph
  {
  private:
    struct Node;
    struct Edge;

  public:
    Graph() = default;
    // Graph(const Graph&);

    // Graph& operator=(const Graph&);

    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight = 2);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    struct Path;
    Path navigate(int start, int finish) const; // как плейсхолдер для функции

    std::ostream& printNodes(std::ostream& = std::cout) const;
    std::ostream& printAllEdges(std::ostream& = std::cout) const;
    bool contains(int nodeName) const;

    std::string name;
    std::string filename;
  private:
    std::map< int, Node > nodes_;

    struct Printer;
    struct Dextra;
  };

  struct Graph::Path
  {
    size_t lenght;
    std::forward_list< int > path;
  };

  struct Graph::Printer
  {
    std::ostream& printUniqueEdges(const Node&, std::ostream&);
    bool hasUniqueEdges(const Node&) const;
    std::unordered_set< int > visitedNodes;
  };

  struct Graph::Dextra
  {
    Dextra(const Graph&);

    Path operator()(int begin, int end);

    void calcMinTimeToEach();
    int getNodeWithMinimumTimeToIt();
    void recalculateTimeToNeighboursOfTheNode(const Node&);
    std::forward_list< int > findShortestPath(int start, int finish);

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
  std::istream& operator>>(std::istream&, Graph&);
}

#endif