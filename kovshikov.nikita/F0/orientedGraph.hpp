#ifndef ORIENTEDGRAPH_HPP
#define ORIENTEDGRAPH_HPP
#include <vector>
#include <string>
#include <cstddef>
#include <map>
#include <utility>

namespace kovshikov
{
  class Graph
  {
  public:
    Graph() = default;
    Graph(const Graph& graph) = default;
    Graph& operator=(const Graph& graph) = default;
    ~Graph() = default;

    class Node;

    void addVertex(size_t key, std::string str);
    void deleteVertex(size_t key);

    void createEdge(size_t keyWho, size_t keyWith, size_t weight);
    void deleteEdge(size_t keyWho, size_t keyWith);
    void increaseWeight(size_t keyWho, size_t keyWith, size_t increase);
    void decreaseWeight(size_t keyWho, size_t keyWith, size_t decrease);
    size_t getWeight(size_t keyWho, size_t keyWith);
    void change(size_t count, size_t who, size_t with);

    void connect(size_t whoKey, size_t count, size_t weight);

    size_t getVertexWeight(size_t key);
    size_t getDegree(size_t key);
    size_t getOwn(size_t key);
    size_t getEdges();

    void haveThisVertex(size_t key);
    void haveNot(size_t keyWho, size_t keyWith);
    bool haveThisKey(size_t key);
    bool isDouble(size_t key1, size_t key2);

    void getConnectKeys(std::vector< size_t >& connectKeys, size_t whoKey);
    std::string getVertex(std::pair< size_t, Node > vertex);
    static size_t getCountEdge(std::pair< size_t, Node > vertex);

    void outGraph(std::ostream& out) const;

    void getMax(std::ostream& out);
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    static bool comp(std::pair< size_t, Node > left, std::pair< size_t, Node > right, Graph& graph);

  private:
    std::map< size_t, Node > tree;
  };

  bool noThis(size_t whoKey, size_t randomKey);

  size_t getKey(std::pair< size_t, Graph::Node > vertex);
  size_t getWith(std::pair< size_t, size_t > edge);
  size_t getWeightEdge(std::pair< size_t, size_t > edge);
}

class kovshikov::Graph::Node
{
public:
  friend class Graph;

  Node() = default;
  Node(std::string str): value(str) {};
  Node(const Node& node) = default;
  Node& operator=(const Node& node) = default;
  ~Node() = default;
private:
  std::map< size_t, size_t> edges;
  std::string value;
};

#endif
