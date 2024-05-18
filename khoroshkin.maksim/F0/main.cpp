#include <functional>
#include "graph.hpp"
#include "commands.hpp"

int main()
{
  using namespace khoroshkin;

  Graph< int > graph;
  std::map< std::string, std::function< void(std::ostream & out) > > availableCmds;
  {
    using namespace std::placeholders;
    availableCmds["help"] = std::bind(khoroshkin::helpCmd, _1);
    availableCmds["open"] = std::bind(khoroshkin::openCmd, std::ref(graph), std::ref(std::cin), _1);
    availableCmds["input"] = std::bind(khoroshkin::inputCmd, std::ref(graph), std::ref(std::cin), _1);
    availableCmds["print"] = std::bind(khoroshkin::printCmd, std::ref(graph), std::ref(std::cin), _1);
    availableCmds["edge"] = std::bind(khoroshkin::edgeCmd, std::ref(graph), std::ref(std::cin), _1);
    availableCmds["sort"] = std::bind(khoroshkin::sortCmd, std::ref(graph), std::ref(std::cin), _1);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      availableCmds.at(cmd)(std::cout);
    }
    catch(const std::exception & e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  return 0;
}
