#include "Commands.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <ScopeGuard.hpp>

double reznikova::getArea(const reznikova::Polygon & polygon)
{
  std::vector< double > sum;
  std::transform(
    polygon.points.begin(),
    polygon.points.end()-1,
    std::next(polygon.points.begin()),
    std::back_inserter(sum),
    [](const Point & a, const Point & b)
    {
      return a.x * b.y - a.y * b.x;
    }
  );
  sum.push_back(polygon.points.back().x * polygon.points.front().y - polygon.points.back().y * polygon.points.front().x);
  double area = std::accumulate(sum.begin(), sum.end(), 0) * 0.5;
  return std::abs(area);
}

size_t reznikova::getNumOfVertexes(const reznikova::Polygon & polygon)
{
  return polygon.points.size();
}


std::vector< reznikova::Polygon > reznikova::chooseOddPolygons(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< Polygon > oddPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(oddPolygons),
    [](const Polygon & polygon)
    {
      return (polygon.points.size() % 2 != 0);
    }
  );
  return oddPolygons;
}

std::vector< reznikova::Polygon > reznikova::chooseEvenPolygons(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(evenPolygons),
    [](const Polygon & polygon)
    {
      return (polygon.points.size() % 2 == 0);
    }
  );
  return evenPolygons;
}

bool reznikova::checkIfSame(size_t num, const reznikova::Polygon & polygon)
{
  return (polygon.points.size() == num);
}

std::vector< reznikova::Polygon > reznikova::chooseNumPolygons(const std::vector< reznikova::Polygon > & polygons, size_t num)
{
  std::vector< Polygon > numPolygons;
  using namespace std::placeholders;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(numPolygons),
    std::bind(checkIfSame, num, _1)
  );
  return numPolygons;
}

std::vector< double > reznikova::getAllAreas(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< double > allAreas;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(allAreas),
    [](const Polygon & polygon)
    {
      return getArea(polygon);
    }
  );
  return allAreas;
}

std::vector< size_t > reznikova::getAllVertexes(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< size_t > allVertexes;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(allVertexes),
    [](const Polygon & polygon)
    {
      return getNumOfVertexes(polygon);
    }
  );
  return allVertexes;
}

double reznikova::getSumArea(const std::vector< reznikova::Polygon > & polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  std::vector< double > allAreas = getAllAreas(polygons);
  return std::accumulate(allAreas.begin(), allAreas.end(), 0.0);
}

void reznikova::areaCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string subCommand;
  is >> subCommand;
  out << std::fixed << std::setprecision(1);
  if (subCommand == "ODD")
  {
    std::vector< Polygon > oddPolygons = chooseOddPolygons(polygons);
    out << getSumArea(oddPolygons) << "\n";
  }
  else if (subCommand == "EVEN")
  {
    std::vector< Polygon > evenPolygons = chooseEvenPolygons(polygons);
    out << getSumArea(evenPolygons) << "\n";
  }
  else if (subCommand == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << getSumArea(polygons)/polygons.size() << "\n";
  }
  else if (!std::isalpha(subCommand[0]) && stoull(subCommand) > 2)
  {
    std::vector< Polygon > numPolygons = chooseNumPolygons(polygons, size_t(stoull(subCommand)));
    out << getSumArea(numPolygons) << "\n";
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void reznikova::maxCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string subCommand;
  is >> subCommand;
  out << std::fixed;
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (subCommand == "AREA")
  {
    std::vector< double > allAreas = getAllAreas(polygons);
    out << std::setprecision(1) << *std::max_element(allAreas.begin(), allAreas.end()) << "\n";
  }
  else if (subCommand == "VERTEXES")
  {
    std::vector< size_t > allAreas = getAllVertexes(polygons);
    out << *std::max_element(allAreas.begin(), allAreas.end()) << "\n";
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void reznikova::minCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string subCommand;
  is >> subCommand;
  out << std::fixed;
  if (subCommand == "AREA")
  {
    std::vector< double > allAreas = getAllAreas(polygons);
    out << std::setprecision(1) << *std::min_element(allAreas.begin(), allAreas.end()) << "\n";
  }
  else if (subCommand == "VERTEXES")
  {
    std::vector< size_t > allAreas = getAllVertexes(polygons);
    out << *std::min_element(allAreas.begin(), allAreas.end()) << "\n";
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void reznikova::countCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string subCommand;
  is >> subCommand;
  out << std::fixed;
  if (subCommand == "EVEN")
  {
    long int numEvenPolygons = 0;
    numEvenPolygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      [](const Polygon & polygon)
      {
        return (polygon.points.size() % 2 == 0);
      }
    );
    out << numEvenPolygons << "\n";
  }
  else if (subCommand == "ODD")
  {
    long int numOddPolygons = 0;
    numOddPolygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      [](const Polygon & polygon)
      {
        return (polygon.points.size() % 2 != 0);
      }
    );
    out << numOddPolygons << "\n";
  }
  else if (!std::isalpha(subCommand[0]) && stoull(subCommand) > 2)
  {
    using namespace std::placeholders;
    long int numSameVertexPolygons = 0;
    numSameVertexPolygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      std::bind(checkIfSame, size_t(std::stoull(subCommand)), _1)
    );
    out << numSameVertexPolygons << "\n";
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

bool reznikova::checkIfPointsEqual(const reznikova::Point & point, const reznikova::Polygon & polygon)
{
  auto numOfPerms = std::count_if(
    polygon.points.begin(),
    polygon.points.end(),
    [point](const Point & compPoint)
    {
      return (compPoint.x == point.x && compPoint.y == point.y) or (compPoint.y == point.x && compPoint.x == point.y);
    }
  );
  return (numOfPerms >= 1);
}

bool reznikova::checkIfPerms(const reznikova::Polygon & basePolygon, const reznikova::Polygon & polygon)
{
  if (basePolygon.points.size() != polygon.points.size())
  {
    return false;
  }
    auto numOfPerms = std::count_if(
    basePolygon.points.begin(),
    basePolygon.points.end(),
    [polygon](const Point & cmpPoint)
    {
      return checkIfPointsEqual(cmpPoint, polygon);
    }
  );
  if (size_t(numOfPerms) == polygon.points.size())
  {
    return true;
  }
  return false;
}

void reznikova::permsCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  Polygon basePolygon;
  is >> basePolygon;
  if (basePolygon.points.size() < 3)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << std::fixed;
  using namespace std::placeholders;
  auto numPerms = std::count_if(
    polygons.begin(),
    polygons.end(),
    std::bind(checkIfPerms, basePolygon, _1)
  );
  out << numPerms << "\n";
}

bool reznikova::checkIfParallelogram(const reznikova::Polygon & polygon)
{
  if (polygon.points.size() == 4)
  {
    Point p1 = polygon.points[0];
    Point p2 = polygon.points[1];
    Point p3 = polygon.points[2];
    Point p4 = polygon.points[3];
    return (((p2.x - p1.x) == (p3.x - p4.x)) && ((p4.y - p1.y) == (p3.y - p2.y)));
  }
  return false;
}

bool reznikova::checkIfRect(const reznikova::Polygon & polygon)
{
    if (polygon.points.size() == 4)
    {
      Point firstPoint = polygon.points[0];
      Point secondPoint = polygon.points[1];
      Point thirdPoint = polygon.points[2];
      Point forthPoint = polygon.points[3];
      if (checkIfParallelogram(polygon))
      {
        int firstOperandLeft = (secondPoint.x - firstPoint.x) * (secondPoint.x - firstPoint.x);
        int firstOperandRight = (forthPoint.y - firstPoint.y) * (forthPoint.y - firstPoint.y);
        int secondOperandLeft = (forthPoint.y - secondPoint.y) * (thirdPoint.y - secondPoint.y);
        int secondOperandRight = (thirdPoint.x - forthPoint.x) * (thirdPoint.x - forthPoint.x);
        return (firstOperandLeft + firstOperandRight) == (secondOperandLeft + secondOperandRight);
      }
    }
    return false;
}

void reznikova::rectsCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out)
{
  out << std::fixed;
  using namespace std::placeholders;
  long int numRects = 0;
  numRects = std::count_if(
    polygons.begin(),
    polygons.end(),
    [](const Polygon & polygon)
    {
      return checkIfRect(polygon);
    }
  );
  out << numRects << "\n";
}

void reznikova::getOutputMessage(std::ostream & out, const std::string & message)
{
  out << message << "\n";
}
