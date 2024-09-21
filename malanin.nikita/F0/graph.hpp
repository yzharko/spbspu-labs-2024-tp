#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <deque>
#include <iostream>

namespace malanin
{
  class Graph
  {
  private:
    struct Node;
    struct Edge;

  public:
    Graph() = default;

    void addNode(int name);
    void addEdge(int lnode, int rnode, size_t weight = 1);
    void rmNode(int name);
    void rmEdge(int lnode, int rnode);

    struct Path;
    Path navigate(int start, int finish) const;
    bool pathExists(int start, int finish) const;
    size_t countPaths(int start, int finish) const;
    Path findAnyPath(int start, int finish) const;
    void printAnyPath(int start, int finish, std::ostream&) const;
    std::forward_list< Path > findAllPaths(int start, int finish) const;
    void printAllPaths(int start, int finish, std::ostream&) const;

    std::ostream& printNodes(std::ostream& = std::cout) const;
    std::ostream& printAllEdges(std::ostream& = std::cout) const;
    bool contains(int nodeName) const;

    std::string name;
    std::string filename;
  private:
    std::map< int, Node > nodes_;

    struct Printer;
    struct DeepDetourer;

    size_t calcPathLength(const std::deque< int >& path) const;
    void printPath(const Path&, std::ostream&) const;
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

  struct Graph::DeepDetourer
  {
    using Path = std::deque< int >;

    DeepDetourer(const Graph&);

    bool checkPathExistance(int begin, int end);
    size_t countPaths(int begin, int end);
    Path findAnyPath(int begin, int end);
    std::forward_list< Path > findAllPaths(int begin, int end);

    bool getPath(int begin, int end, Path& path);
    void getAllPaths(int begin, int end, std::forward_list< Path >& paths, Path curPath);
    bool doPathContainsNode(int node, const Path& path);

    std::unordered_set< int > passedNodes_;
    const Graph& graph_;
  };

  struct Graph::Edge
  {
    int dest;
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
