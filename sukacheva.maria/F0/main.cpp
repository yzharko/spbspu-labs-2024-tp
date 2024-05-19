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

  auto distances = graph.dijkstra(0);

  for (std::map< size_t, size_t >::iterator it = distances.begin(); it != distances.end(); it++)
  {
    std::cout << "Distance from A to " << graph.VertexesList[it->first] << ": " << it->second << std::endl;
  }
}
