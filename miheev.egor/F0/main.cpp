#include <iostream>
#include "graph.hpp"

int main()
{
  using namespace miheev;
  Graph g;
  g.setName("TEST");
  std::cout << g.getName() << '\n';
  g.addNode(1);
  g.addNode(2);
  g.addEdge(1, 2);
  g.addNode(3);
  g.addNode(4);
  g.addEdge(1, 4);
  g.addEdge(2, 4);
  g.addEdge(1, 3);
  g.printNodes(std::cout);
  g.printAllEdges(std::cout);
  return 0;
}