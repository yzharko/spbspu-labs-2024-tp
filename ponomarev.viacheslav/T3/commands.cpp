#include "commands.hpp"
#include <functional>
#include <cctype>
#include "polygonFunctions.hpp"
#include <vector>
#include <iomanip>
#include <numeric>

using namespace std::placeholders;

std::ostream & ponomarev::chooseAreaCommand(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::function< double (const std::vector< Polygon > & data) > > areaCommands;
  {
    areaCommands["EVEN"] = sumAreasEven;
  }

  std::string type;
  in >> type;
  out << std::fixed << std::setprecision(1);
  try
  {
    out << areaCommands.at(type)(data) << "\n";
  }
  catch(const std::out_of_range & e)
  {
    if (std::isdigit(type[0]) && std::stoull(type) > 2)
    {
      out << countSumAreasVertexes(data, std::stoull(type)) << "\n";
    }
    else
    {
      throw std::logic_error("Wrong parameter");
    }
  }

  return out;
}

double ponomarev::sumAreasEven(const std::vector< Polygon > & data)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, sumEven);
}

double ponomarev::countSumAreasVertexes(const std::vector< Polygon > & data, int numOfVertexes)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, std::bind(sumIfNumOfVertexes, _1, _2, numOfVertexes));
}

std::ostream & ponomarev::printMessage(std::ostream & out, const std::string & message)
{
  out << message << '\n';
  return out;
}
