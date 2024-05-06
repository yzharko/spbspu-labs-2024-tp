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
      out << std::accumulate(std::begin(d), std::end(d), 0.0, std::bind(addEqualVertexes, _1, _2, vetrCount)) << '\n';
    }
  }
  return out;
}

std::ostream& miheev::maxCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    std::vector< double > areas;
    std::transform(std::begin(d), std::end(d), std::back_inserter(areas), miheev::getArea);
    double maximum = *std::max_element(areas.begin(), areas.end());
    out << maximum;
  }
  else if (arg == "VERTEXES")
  {
    std::vector< size_t > vertexesCounts;
    std::transform(std::begin(d), std::end(d), std::back_inserter(vertexesCounts), miheev::countVertexes);
    size_t maximum = *std::max_element(vertexesCounts.begin(), vertexesCounts.end());
    out << maximum << '\n';
  }
  return out;
}

std::ostream& miheev::minCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    std::vector< double > areas;
    std::transform(std::begin(d), std::end(d), std::back_inserter(areas), miheev::getArea);
    double maximum = *std::min_element(areas.begin(), areas.end());
    out << maximum;
  }
  else if (arg == "VERTEXES")
  {
    std::vector< size_t > vertexesCounts;
    std::transform(std::begin(d), std::end(d), std::back_inserter(vertexesCounts), miheev::countVertexes);
    size_t maximum = *std::min_element(vertexesCounts.begin(), vertexesCounts.end());
    out << maximum << '\n';
  }
  return out;
}

bool isOddVertexes(const miheev::Polygon& polygon)
{
  return !(miheev::countVertexes(polygon) % 2);
}

bool isEvenVertexes(const miheev::Polygon& polygon)
{
  return !isOddVertexes(polygon);
}

bool isEqualVertexes(const miheev::Polygon& polygon, size_t vertexes)
{
  return miheev::countVertexes(polygon) == vertexes;
}

std::ostream& miheev::countCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  if (arg == "EVEN")
  {
    out << std::count_if(std::begin(d), std::end(d), isEvenVertexes) << '\n';
  }
  else if (arg == "ODD")
  {
    out << std::count_if(std::begin(d), std::end(d), isOddVertexes) << '\n';
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
      out << std::count_if(std::begin(d), std::end(d), std::bind(isEqualVertexes, _1, vetrCount)) << '\n';
    }
  }
  return out;
}

struct SamePolygonSeries
{
public:
  size_t operator()(const miheev::Polygon&, const miheev::Polygon&);

private:
  size_t series_;
};

size_t SamePolygonSeries::operator()(const miheev::Polygon& polygon, const miheev::Polygon& cmp)
{
  if (polygon == cmp)
  {
    series_++;
  }
  else
  {
    series_ = 0;
  }
  return series_;
}


std::ostream& miheev::maxseqCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  Polygon arg;
  in >> arg;
  
  return out;
}
