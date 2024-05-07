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
  if (miheev::countVertexes(polygon) % 2)
  {
    return accumulator + miheev::getArea(polygon);
  }
  return accumulator;
}

double addEvenArea(double accumulator, const miheev::Polygon& polygon)
{
  if (!(miheev::countVertexes(polygon) % 2))
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
    out << maximum << '\n';
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
  return miheev::countVertexes(polygon) % 2;
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

std::ostream& miheev::maxseqCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon >& d)
{
  if (d.empty())
  {
    throw std::logic_error("No shapes passed");
  }
  Polygon arg;
  in >> arg;
  std::vector< size_t > countInARow;
  SamePolygonSeries series;
  {
    using namespace std::placeholders;
    std::transform(
      std::begin(d),
      std::end(d),
      std::back_inserter(countInARow),
      std::bind(series, _1, arg)
    );
  }
  out << *std::max_element(std::begin(countInARow), std::end(countInARow)) << '\n';
  return out;
}

miheev::Point makeVector(const miheev::Point& lhs, const miheev::Point& rhs)
{
  return miheev::Point{lhs.x - rhs.x, lhs.y - rhs.y};
}

bool arePerpendicular(const miheev::Point vec1, const miheev::Point vec2)
{
  return vec1.x * vec2.x - vec1.y * vec2.y == 0;
}

bool hasPerpendecular(const miheev::Polygon& polygon)
{
  std::vector< miheev::Point > vectors;
  std::transform(
    std::begin(polygon.points) + 1,
    std::end(polygon.points),
    std::begin(polygon.points),
    std::back_inserter(vectors),
    makeVector
  );
  std::vector< bool > vertexesPerpendicularity;
  std::transform(
    std::begin(vectors) + 1,
    std::end(vectors),
    std::begin(vectors),
    std::back_inserter(vertexesPerpendicularity),
    arePerpendicular
  );
  return std::any_of(
    std::begin(vertexesPerpendicularity),
    std::end(vertexesPerpendicularity),
    [] (bool val)
    {
      return val;
    }
  );
}

std::ostream& miheev::rightshapesCommand(std::istream&, std::ostream& out, const std::vector< miheev::Polygon >& d)
{
  std::vector< bool > hasPerp;
  std::transform(
    std::begin(d),
    std::end(d),
    std::back_inserter(hasPerp),
    hasPerpendecular
  );
  size_t rightsTotal = std::count(
    std::begin(hasPerp),
    std::end(hasPerp),
    true
  );
  out << rightsTotal << '\n';
  return out;
}
