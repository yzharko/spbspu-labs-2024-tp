#include "commands.hpp"
#include <functional>
#include <cctype>
#include "polygonFunctions.hpp"
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>

using namespace std::placeholders;

std::ostream & ponomarev::chooseAreaCommand(std::istream & in, std::ostream & out, const std::vector< Polygon > & data)
{
  std::map< std::string, std::function< double (const std::vector< Polygon > & data) > > areaCommands;
  {
    areaCommands["EVEN"] = sumAreasEven;
    areaCommands["ODD"] = sumAreasOdd;
    areaCommands["MEAN"] = countAreasMean;
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

std::ostream & ponomarev::getMax(std::istream & in, std::ostream & out, const std::vector< Polygon > & data)
{
  std::map< std::string, std::function< double (const std::vector< Polygon > & data) > > maxCommands;
  {
    maxCommands["AREA"] = getMaxArea;
    maxCommands["VERTEXES"] = getMaxVertexes;
  }

  std::string type;
  in >> type;
  out << std::fixed << std::setprecision(1);
  try
  {
    out << maxCommands.at(type)(data) << "\n";
  }
  catch(const std::out_of_range & e)
  {
    throw std::logic_error("Wrong parameter");
  }

  return out;
}

double ponomarev::sumAreasEven(const std::vector< Polygon > & data)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, sumEven);
}

double ponomarev::sumAreasOdd(const std::vector< Polygon > & data)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, sumOdd);
}

double ponomarev::countAreasMean(const std::vector< Polygon > & data)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, sumAll) / data.size();
}

double ponomarev::countSumAreasVertexes(const std::vector< Polygon > & data, int numOfVertexes)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, std::bind(sumIfNumOfVertexes, _1, _2, numOfVertexes));
}

double ponomarev::getMaxArea(const std::vector< Polygon > & data)
{
  std::vector< double > areas(data.size());
  std::transform(data.begin(), data.end(), areas.begin(), getArea);
  double maxArea = *std::max_element(areas.begin(), areas.end());
  return maxArea;
}

double ponomarev::getMaxVertexes(const std::vector< Polygon > & data)
{
  std::vector< int > numsOfVertexes(data.size());
  std::transform(data.begin(), data.end(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::max_element(numsOfVertexes.begin(), numsOfVertexes.end());
  return maxVertexes;
}

std::ostream & ponomarev::printMessage(std::ostream & out, const std::string & message)
{
  out << message << '\n';
  return out;
}
