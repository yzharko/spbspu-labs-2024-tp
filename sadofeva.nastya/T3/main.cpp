#include <iostream>
#include <limits>
#include <iterator>
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
  commands["AREA"] = std::bind(commandArea, _1, _2, polygons);
  commands["MAX"] = std::bind(commandMax, _1, _2, polygons);
  command["MIN"] = std::bind(commandMin, _1, _2, polygons);
  command["COUNT"] = std::bind(commandCount, _1, _2, polygons);
  command["SAME"] = std::bind(commandSame, _1, _2, polygons);
  command["INFRAME"] = std::bind(commandFrame, _1, _2, polygons);

  std::string command = "";
  while ( std::cin >> command)
  {
    try
    {
       command.at(command)(std::cin,std::cout, polygons);
       std::cout << "\n";
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
