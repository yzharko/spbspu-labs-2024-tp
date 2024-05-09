#include <iostream>
#include "graph.hpp"

int main()
{
  using namespace miheev;
  Graph g;
  g.setName("TEST");
  std::cout << g.getName() << '\n';
  // g.addNode(1);
  // g.addNode(2);
  // g.addNode(3);
  // g.addNode(4);
  // g.addEdge(1, 3, 5);
  // g.addEdge(1, 2, 3);
  // g.addEdge(2, 4, 7);
  // g.addEdge(3, 4, 2);
  g.addNode(1);
  g.addNode(2);
  g.addNode(3);
  g.addNode(4);
  g.addNode(5);
  g.addNode(6);
  g.addNode(7);

  g.addEdge(1, 3, 7);
  g.addEdge(1, 2, 5);
  g.addEdge(2, 4, 13);
  g.addEdge(2, 7, 9);
  g.addEdge(3, 4, 42);
  g.addEdge(3, 6, 7);
  g.addEdge(4, 7, 5);
  g.addEdge(4, 5, 22);
  g.addEdge(5, 6, 3);
  g.addEdge(5, 7, 2);
  g.printNodes(std::cout);
  g.printAllEdges(std::cout);
  Graph::Path p = g.navigate(1, 5);
  std::cout << p.lenght << '\n';
  return 0;
}