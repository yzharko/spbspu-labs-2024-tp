#include "commands.hpp"
#include <functional>
#include <map>
#include <cctype>
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
    areaCommands["MEAN"] = sumAreasMean;
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
      out << sumAreasVertexes(data, std::stoull(type)) << "\n";
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

  if (data.empty())
  {
    throw std::logic_error("error: data is empty");
  }

  std::string type;
  in >> type;
  if (type == "AREA")
  {
    out << std::fixed << std::setprecision(1);
  }
  else
  {
    out << std::fixed << std::setprecision(0);
  }

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

std::ostream & ponomarev::getMin(std::istream & in, std::ostream & out, const std::vector< Polygon > & data)
{
  std::map< std::string, std::function< double (const std::vector< Polygon > & data) > > minCommands;
  {
    minCommands["AREA"] = getMinArea;
    minCommands["VERTEXES"] = getMinVertexes;
  }

  std::string type;
  in >> type;
  if (type == "AREA")
  {
    out << std::fixed << std::setprecision(1);
  }
  else
  {
    out << std::fixed << std::setprecision(0);
  }

  try
  {
    out << minCommands.at(type)(data) << "\n";
  }
  catch(const std::out_of_range & e)
  {
    throw std::logic_error("Wrong parameter");
  }

  return out;
}

std::ostream & ponomarev::count(std::istream & in, std::ostream & out, const std::vector< Polygon > & data)
{
  std::map< std::string, std::function< double (const std::vector< Polygon > & data) > > countCommands;
  {
    countCommands["EVEN"] = countEven;
    countCommands["ODD"] = countOdd;
  }

  std::string type;
  in >> type;
  try
  {
    out << countCommands.at(type)(data) << "\n";
  }
  catch(const std::out_of_range & e)
  {
    if (std::isdigit(type[0]) && std::stoull(type) > 2)
    {
      out << countCertain(data, std::stoull(type)) << "\n";
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

double ponomarev::sumAreasOdd(const std::vector< Polygon > & data)
{
  return std::accumulate(data.cbegin(), data.cend(), 0, sumOdd);
}

double ponomarev::sumAreasMean(const std::vector< Polygon > & data)
{
  if (data.empty())
  {
    throw std::logic_error("error: data is empty");
  }

  double res = std::accumulate(data.cbegin(), data.cend(), 0, sumAll);
  return res / data.size();
}

double ponomarev::sumAreasVertexes(const std::vector< Polygon > & data, int numOfVertexes)
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

double ponomarev::getMinArea(const std::vector< Polygon > & data)
{
  std::vector< double > areas(data.size());
  std::transform(data.begin(), data.end(), areas.begin(), getArea);
  double minArea = *std::min_element(areas.begin(), areas.end());
  return minArea;
}

double ponomarev::getMinVertexes(const std::vector< Polygon > & data)
{
  std::vector< int > numsOfVertexes(data.size());
  std::transform(data.begin(), data.end(), numsOfVertexes.begin(), getNumOfVertexes);
  int minVertexes = *std::min_element(numsOfVertexes.begin(), numsOfVertexes.end());
  return minVertexes;
}

int ponomarev::countEven(const std::vector< Polygon > & data)
{
  return std::count_if(data.begin(), data.end(), isEven);
}

int ponomarev::countOdd(const std::vector< Polygon > & data)
{
  return std::count_if(data.begin(), data.end(), isOdd);
}

int ponomarev::countCertain(const std::vector< Polygon > & data, int numOfVertexes)
{
  return std::count_if(data.begin(), data.end(), std::bind(isEqually, _1, numOfVertexes));
}

std::ostream & ponomarev::countRects(std::istream &, std::ostream & out, const std::vector< Polygon > & data)
{
  int numRects = std::count_if(data.begin(), data.end(), isRect);
  out << std::fixed << std::setprecision(0) << numRects << "\n";
  return out;
}

std::ostream & ponomarev::countIntersections(std::istream & in, std::ostream & out, const std::vector< Polygon > & data)
{
  Polygon comparationPolygon;
  if (!(in >> comparationPolygon))
  {
    throw std::logic_error("wrong polygon");
  }

  int numIntersections = std::count_if(data.begin(), data.end(), std::bind(isIntersection, _1, comparationPolygon));
  out << std::fixed << std::setprecision(0) << numIntersections << "\n";
  return out;
}

std::ostream & ponomarev::printInvalidCommandMessage(std::ostream & out)
{
  std::string message = "<INVALID COMMAND>";
  out << message << '\n';
  return out;
}
