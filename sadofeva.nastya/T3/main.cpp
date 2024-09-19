#include <iostream>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include "Point.hpp"
#include "command.hpp"

using namespace sadofeva;

int main(int argc, char* argv[])
{
  std::vector < Polygon > polygons;
  if (argc != 2)
  {
    std::cerr << "Wrond input\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  using input_it_t = std::istream_iterator< Polygon >;

  while (!input.eof())
  {
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(polygons));
  }

  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream& , const std::vector< Polygon>&) > > commands;
  commands["AREA"] = std::bind(commandArea, polygons, _1, _2);
  commands["MAX"] = std::bind(commandMax, polygons, _1, _2);
  commands["MIN"] = std::bind(commandMin, polygons, _1, _2);
  commands["COUNT"] = std::bind(commandCount, polygons, _1, _2);
  commands["SAME"] = std::bind(commandSame, polygons, _1, _2);
  commands["INFRAME"] = std::bind(commandFrame, polygons, _1, _2);

  std::string command = "";
  while ( std::cin >> command)
  {
    try
    {
       commands.at(command)(std::cin,std::cout, polygons);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}

