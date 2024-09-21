#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <limits>
#include <functional>
#include <iterator>
#include "Polygon.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    std::string fname = argv[1];
    std::ifstream file(fname);
    std::vector< malanin::Polygon > polygons;
    using inputIt = std::istream_iterator< malanin::Polygon >;
    while (!file.eof())
    {
      std::copy(inputIt{ file }, inputIt{}, std::back_inserter(polygons));
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::map < std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
      using namespace std::placeholders;
      commands["AREA"] = std::bind(malanin::doAreaCommand, std::cref(polygons), _1, _2);
      commands["MAX"] = std::bind(malanin::doMaxCommand, std::cref(polygons), _1, _2);
      commands["MIN"] = std::bind(malanin::doMinCommand, std::cref(polygons), _1, _2);
      commands["COUNT"] = std::bind(malanin::doCountCommand, std::cref(polygons), _1, _2);
      commands["RECTS"] = std::bind(malanin::doRectsCommand, std::cref(polygons), _2);
      commands["MAXSEQ"] = std::bind(malanin::doMaxseqCommand, std::cref(polygons), _1, _2);
    }

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        commands.at(cmd)(std::cin, std::cout);
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    file.close();
  }
  else
  {
    std::cerr << "not file" << "\n";
    return 1;
  }
  return 0;
}
