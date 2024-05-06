#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <functional>
#include "scopeguard.hpp"

double addArea(double accumulator, const miheev::Polygon& polygon)
{
  return accumulator + miheev::getArea(polygon);
}

double addOddArea(double accumulator, const miheev::Polygon& polygon)
{
  if (!(miheev::countVertexes(polygon) % 2))
  {
    return accumulator + miheev::getArea(polygon);
  }
  return accumulator;
}

double addEvenArea(double accumulator, const miheev::Polygon& polygon)
{
  if (miheev::countVertexes(polygon) % 2)
  {
    return accumulator + miheev::getArea(polygon);
  }
  return accumulator;
}

double addEqualVertexes(double accumulator, const miheev::Polygon& polygon, size_t vertexes)
{
  if (miheev::countVertexes(polygon) == vertexes)
  {
    return accumulator + miheev::getArea(polygon);
  }
  return accumulator;
}

std::ostream& miheev::areaCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon >& d)
{
  iofmtguard fguard(out);
  std::string arg = "";
  in >> arg;
  out << std::fixed << std::setprecision(1);
  if (arg == "MEAN")
  {
    out << std::accumulate(std::cbegin(d), std::cend(d), 0.0, addArea) / d.size() << '\n';
  }
  else if (arg == "ODD")
  {
    out << std::accumulate(std::begin(d), std::end(d), 0.0, addOddArea) << '\n';
  }
  else if (arg == "EVEN")
  {
    out << std::accumulate(std::begin(d), std::end(d), 0.0, addEvenArea) << '\n';
  }
  else
  {
    size_t vetrCount = std::stoull(arg);
    if (vetrCount < 3)
    {
      throw std::logic_error("Too few vertexes\n");
    }
    {
      using namespace std::placeholders;
      out << std::accumulate(std::begin(d), std::end(d), 0.0, std::bind(addEqualVertexes, _1, _2, vetrCount));
    }
  }
  return out;
}

std::ostream& maxCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  if (arg == "AREA")
  {
    std::vector< double > areas;
    std::transform(std::begin(d), std::end(d), std::back_inserter(areas), miheev::getArea);
    std::sort(std::begin(d), std::end(d));
    out << areas.back() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector< size_t > vertexesCounts;
    std::transform(std::begin(d), std::end(d), std::back_inserter(vertexesCounts), miheev::countVertexes);
    std::sort(std::begin(d), std::end(d));
    out << vertexesCounts.back();
  }
}
