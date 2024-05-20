#include <iostream>
#include "graph.hpp"

int main()
{
  using namespace sukacheva;
  Graph graph("ExampleGraph");

  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");

  graph.addEdge("A", "B", 1);
  graph.addEdge("A", "C", 4);
  graph.addEdge("B", "C", 2);
  graph.addEdge("B", "D", 5);
  graph.addEdge("C", "D", 1);

  size_t start = graph.getVertexIndex("A");
  size_t end = graph.getVertexIndex("D");
  std::pair<std::map<size_t, size_t>, std::map<size_t, size_t>> dijkstra = graph.dijkstraDistances("A");

  std::cout << "Shortest distance from A to D: " << dijkstra.first[end] << std::endl;

  std::vector< std::string > path = graph.dijkstraPath(dijkstra.second, "A", "D");
  std::cout << "Path: ";
  for (std::vector< std::string >::iterator it = path.begin(); it != path.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return 0;
}
