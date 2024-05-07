#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <functional>
#include <scopeguard.hpp>

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

double calcMeanArea(const std::vector< miheev::Polygon >& data)
{
    if (data.empty())
    {
      throw std::logic_error("Zero division: no shapes to calc mean causes zero division");
    }
    return std::accumulate(std::cbegin(data), std::cend(data), 0.0, addArea) / data.size();
}

double calcOddArea(const std::vector< miheev::Polygon >& data)
{
  return std::accumulate(std::begin(data), std::end(data), 0.0, addOddArea);
}

double calcEvenArea(const std::vector< miheev::Polygon >& data)
{
  return std::accumulate(std::begin(data), std::end(data), 0.0, addEvenArea);
}

double calcVertexesArea(const std::vector< miheev::Polygon >& data, size_t vertexes)
{
    if (vertexes < 3)
    {
      throw std::logic_error("Too few vertexes\n");
    }
    {
      using namespace std::placeholders;
      return std::accumulate(std::begin(data), std::end(data), 0.0, std::bind(addEqualVertexes, _1, _2, vertexes));
    }
}

std::ostream& miheev::areaCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon >& d)
{
  iofmtguard fguard(out);
  std::string arg = "";
  in >> arg;
  out << std::fixed << std::setprecision(1);
  if (arg == "MEAN")
  {
    sendMessage(out, calcMeanArea(d));
  }
  else if (arg == "ODD")
  {
    sendMessage(out, calcOddArea(d));
  }
  else if (arg == "EVEN")
  {
    sendMessage(out, calcEvenArea(d));
  }
  else
  {
    size_t vertCount = std::stoull(arg);
    sendMessage(out, calcVertexesArea(d, vertCount));
  }
  return out;
}

double maxArea(const std::vector< miheev::Polygon >& data)
{
  std::vector< double > areas;
  std::transform(std::begin(data), std::end(data), std::back_inserter(areas), miheev::getArea);
  double maximum = *std::max_element(areas.begin(), areas.end());
  return maximum;
}

size_t maxVertexes(const std::vector< miheev::Polygon >& data)
{
  std::vector< size_t > vertexesCounts;
  std::transform(std::begin(data), std::end(data), std::back_inserter(vertexesCounts), miheev::countVertexes);
  size_t maximum = *std::max_element(vertexesCounts.begin(), vertexesCounts.end());
  return maximum;
}

std::ostream& miheev::maxCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  if (d.empty())
  {
    throw std::logic_error("Empty list of shapes passed");
  }
  std::string arg = "";
  in >> arg;
  iofmtguard fguard(out);
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    sendMessage(out, maxArea(d));
  }
  else if (arg == "VERTEXES")
  {
    sendMessage(out, std::to_string(maxVertexes(d)));
  }
  else
  {
    throw std::logic_error("No such parameter");
  }
  return out;
}

double minArea(const std::vector< miheev::Polygon >& data)
{
  std::vector< double > areas;
  std::transform(std::begin(data), std::end(data), std::back_inserter(areas), miheev::getArea);
  double minimum = *std::min_element(areas.begin(), areas.end());
  return minimum;
}

size_t minVertexes(const std::vector< miheev::Polygon >& data)
{
  std::vector< size_t > vertexesCounts;
  std::transform(std::begin(data), std::end(data), std::back_inserter(vertexesCounts), miheev::countVertexes);
  size_t minimum = *std::min_element(vertexesCounts.begin(), vertexesCounts.end());
  return minimum;
}
std::ostream& miheev::minCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  out << std::fixed << std::setprecision(1);
  if (arg == "AREA")
  {
    sendMessage(out, minArea(d));
  }
  else if (arg == "VERTEXES")
  {
    sendMessage(out, minVertexes(d));
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

size_t countEven(const std::vector< miheev::Polygon >& data)
{
  return std::count_if(std::begin(data), std::end(data), isEvenVertexes);
}

size_t countOdd(const std::vector< miheev::Polygon >& data)
{
  return std::count_if(std::begin(data), std::end(data), isOddVertexes);
}

size_t countPolysWithVertexes(const std::vector< miheev::Polygon >& data, size_t vertexes)
{
  if (vertexes < 3)
  {
    throw std::logic_error("Too few vertexes\n");
  }
  using namespace std::placeholders;
  return std::count_if(std::begin(data), std::end(data), std::bind(isEqualVertexes, _1, vertexes));
}

std::ostream& miheev::countCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon>& d)
{
  std::string arg = "";
  in >> arg;
  if (arg == "EVEN")
  {
    sendMessage(out, std::to_string(countEven(d)));
  }
  else if (arg == "ODD")
  {
    sendMessage(out, std::to_string(countOdd(d)));
  }
  else
  {
    size_t vetrCount = std::stoull(arg);
    sendMessage(out, std::to_string(countPolysWithVertexes(d, vetrCount)));
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

size_t maxSeries(const std::vector< miheev::Polygon >& data, const miheev::Polygon& benchmark)
{
  std::vector< size_t > countInARow;
  SamePolygonSeries series;
  {
    using namespace std::placeholders;
    std::transform(
      std::begin(data),
      std::end(data),
      std::back_inserter(countInARow),
      std::bind(series, _1, benchmark)
    );
  }
  size_t maximum = *std::max_element(std::begin(countInARow), std::end(countInARow));
  return maximum;
}

std::ostream& miheev::maxseqCommand(std::istream& in, std::ostream& out, const std::vector< miheev::Polygon >& d)
{
  if (d.empty())
  {
    throw std::logic_error("No shapes passed");
  }
  Polygon arg;
  in >> arg;
  if (in.fail())
  {
    throw std::logic_error("Inappropriate input format");
  }
  if (arg.points.size() < 3)
  {
    throw std::logic_error("Inappropriate size");
  }
  size_t maximum = maxSeries(d, arg);
  if (maximum == 0)
  {
    throw std::runtime_error("Such rect Doesnt exist");
  }
  sendMessage(out, std::to_string(maximum));
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
  vectors.push_back(makeVector(polygon.points.front(), polygon.points.back()));
  std::vector< bool > vertexesPerpendicularity;
  std::transform(
    std::begin(vectors) + 1,
    std::end(vectors),
    std::begin(vectors),
    std::back_inserter(vertexesPerpendicularity),
    arePerpendicular
  );
  vertexesPerpendicularity.push_back(arePerpendicular(vectors.front(), vectors.back()));
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

std::ostream& miheev::sendMessage(std::ostream& out, const std::string& message)
{
  out << message << '\n';
  return out;
}

std::ostream& miheev::sendMessage(std::ostream& out, double message)
{
  iofmtguard fguard(out);
  out << std::fixed << std::setprecision(1);
  return out << message << '\n';
}
