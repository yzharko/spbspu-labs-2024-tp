k#include <iostream>
#include <map>
#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <exception>
#include <iterator>
#include <fstream>
#include "InputProcessing.hpp"
#include "Commands.hpp"

int main(int argc, const char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "wrong number of args\n";
    return 1;
  }
  std::vector< reznikova::Polygon > inputData;
  std::ifstream input(argv[1]);
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< reznikova::Polygon >{input},
      std::istream_iterator< reznikova::Polygon >{},
      std::back_inserter(inputData)
    );
    if (input.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(const std::vector< reznikova::Polygon >&, std::ostream&, std::istream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(reznikova::areaCommand, _1, _2, _3);
    commands["MAX"] = std::bind(reznikova::maxCommand, _1, _2, _3);
    commands["MIN"] = std::bind(reznikova::minCommand, _1, _2, _3);
    commands["COUNT"] = std::bind(reznikova::countCommand, _1, _2, _3);
    commands["PERMS"] = std::bind(reznikova::permsCommand, _1, _2, _3);
    commands["RECTS"] = std::bind(reznikova::rectsCommand, _1, _2);
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(inputData, std::cout, std::cin);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
