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
  return 0;
}