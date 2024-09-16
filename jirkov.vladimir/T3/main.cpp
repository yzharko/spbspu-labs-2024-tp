#include <iostream>
#include <iterator>
#include <map>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <functional>
#include <limits>
#include "geoStructures.hpp"
#include "Commands.hpp"
int main(int argc, char ** argv)
{
  using namespace jirkov;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  using input_iterator_t = std::istream_iterator< Polygon >;
  std::ifstream in(argv[1]);
  std::vector< Polygon > allData;
  while (!in.eof())
  {
    std::copy(input_iterator_t{in}, input_iterator_t{}, std::back_inserter(allData));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::istream&, std::ostream&) > > interaction;
  {
    using namespace std::placeholders;
    interaction["AREA"] = std::bind(jirkov::getArea, _1, _2, _3);
    //interaction["MAX"] = std::bind(jirkov::getMax, _1, _2, _3);
    //interaction["MIN"] = std::bind(jirkov::getMin, _1, _2, _3);
    //interaction["COUNT"] = std::bind(jirkov::count, _1, _2, _3);
    //interaction["LESSAREA"] = std::bind(jirkov::getLessArea, _1, _3);
    //interaction["PERMS"] = std::bind(jirkov::checkPerms, _1, _2, _3);
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      interaction.at(command)(allData, std::cin, std::cout);
    }
    catch(const std::out_of_range& error)
    {
      std::cerr << "INVALID COMMAND" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
