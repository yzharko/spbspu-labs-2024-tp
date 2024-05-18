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
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void outKeys(); // вывод всех ключей нужен ли
    void outGraph() const; //вывод ключа, вершины, ребер

    void createEdge(size_t keyWho, size_t keyWith, size_t weight);
    void decreaseWeight(size_t keyWho, size_t keyWith, size_t decrease);
    void increaseWeight(size_t keyWho, size_t keyWith, size_t increase);
    size_t getWeight(size_t keyWho, size_t keyWith);
    void deleteEdge(size_t keyWho, size_t keyWith);

    void connect(size_t whoKey, size_t count, size_t weight);
    void getConnectKeys(std::vector< size_t >& connectKeys, size_t whoKey);

    bool haveThisKey(size_t key);
    std::string getVertex(std::pair< size_t, Node > vertex);
    void haveNot(size_t keyWho, size_t keyWith);
    bool isDouble(size_t key1, size_t key2);
    void deleteVertex(size_t key);
    size_t getDegree(size_t key);
  private:
    std::map< size_t, Node > tree;
  };

  size_t getKey(std::pair< size_t, Graph::Node > vertex);
  bool noThis(size_t whoKey, size_t randomKey);
  size_t getWith(std::pair< size_t, size_t > edge);
  bool noThisEl(size_t whoKey, std::pair< size_t, Graph::Node > el);
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
