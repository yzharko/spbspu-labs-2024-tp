#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <map>
#include <functional>
#include <string>

double sukacheva::calculateTriangleArea(Point p1, Point p2, Point p3)
{
  return 0.5 * abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)));
}

double sukacheva::calculatePolygonArea(std::vector<Point> polygon, size_t n)
{
  if (n < 3)
  {
    return 0;
  }
  else
  {
    return calculateTriangleArea(polygon[0], polygon[n - 1], polygon[n - 2]) + calculatePolygonArea(polygon, n - 1);
  }
}

double sukacheva::addArea(double area, Polygon applicant)
{
  return area + sukacheva::calculatePolygonArea(applicant.points, applicant.points.size());
}

void sukacheva::oddArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< Polygon > oddPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(oddPolygons),
    [](const Polygon& applicant)
    {
      return (applicant.points.size() % 2);
    }
  );
  double result = std::accumulate(oddPolygons.begin(), oddPolygons.end(), 0.0, addArea);
  out << std::setprecision(1) << result << '\n';
}

void sukacheva::evenArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(evenPolygons),
    [](const Polygon& applicant)
    {
      return !(applicant.points.size() % 2);
    }
  );
  double result = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, addArea);
  out << std::fixed << std::setprecision(1) << result << '\n';
}

void sukacheva::meanArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  if (allPolygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  double result = std::accumulate(allPolygons.begin(), allPolygons.end(), 0.0, addArea) / allPolygons.size();
  out << std::fixed << std::setprecision(1) << result << '\n';
}

void sukacheva::verticesArea(const std::vector<Polygon>& allPolygons, std::ostream& out, size_t vertices)
{
  std::vector< Polygon > verticesPolygons;
  std::copy_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(verticesPolygons),
    [vertices](const Polygon& applicant)
    {
      return (applicant.points.size() == vertices);
    }
  );
  double result = std::accumulate(verticesPolygons.begin(), verticesPolygons.end(), 0.0, addArea);
  out << std::fixed << std::setprecision(1) << result << '\n';
}

void sukacheva::maxArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< double > allAreas;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allAreas),
    [](const Polygon& applicant)
    {
      return calculatePolygonArea(applicant.points, applicant.points.size());
    }
  );
  double maxElement = *std::max_element(allAreas.begin(), allAreas.end());
  out << std::fixed << std::setprecision(1) << maxElement << '\n';
}

void sukacheva::maxVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< size_t > allVertices;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allVertices),
    [](const Polygon& applicant)
    {
      return (applicant.points.size());
    }
  );
  size_t maxElement = *std::max_element(allVertices.begin(), allVertices.end());
  out << std::fixed << maxElement << '\n';
}

void sukacheva::minArea(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< double > allAreas;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allAreas),
    [](const Polygon& applicant)
    {
      return calculatePolygonArea(applicant.points, applicant.points.size());
    }
  );
  double minElement = *std::min_element(allAreas.begin(), allAreas.end());
  out << std::fixed << std::setprecision(1) << minElement << '\n';
}

void sukacheva::minVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  std::vector< size_t > allVertices;
  std::transform
  (
    allPolygons.begin(),
    allPolygons.end(),
    std::back_inserter(allVertices),
    [](const Polygon& applicant) -> size_t
    {
      return applicant.points.size();
    }
  );
  size_t minElement = *std::min_element(allVertices.begin(), allVertices.end());
  out << std::fixed << minElement << '\n';
}

void sukacheva::countEvenVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant)
    {
      return !(applicant.points.size() % 2);
    }
  );
  out << std::fixed << count << '\n';
}

void sukacheva::countOddVertices(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant)
    {
      return (applicant.points.size() % 2);
    }
  );
  out << std::fixed << count << '\n';
}

void sukacheva::countVertices(const std::vector<Polygon>& allPolygons, std::ostream& out, size_t vertices)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [vertices](const Polygon& applicant)
    {
      return (applicant.points.size() == vertices);
    }
  );
  out << std::fixed << count << '\n';
}

void sukacheva::commandArea(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["EVEN"] = std::bind(evenArea, _1, _2);
  commandKey["ODD"] = std::bind(oddArea, _1, _2);
  commandKey["MEAN"] = std::bind(meanArea, _1, _2);
  std::string command;
  in >> command;
  try
  {
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    if (!std::isalpha(command[0]))
    {
      size_t vertices = std::stoull(command);
      if (vertices < 3)
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
      verticesArea(allPolygons, out, vertices);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}

void sukacheva::commandMax(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["AREA"] = std::bind(maxArea, _1, _2);
  commandKey["VERTEXES"] = std::bind(maxVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    if (allPolygons.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void sukacheva::commandMin(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["AREA"] = std::bind(minArea, _1, _2);
  commandKey["VERTEXES"] = std::bind(minVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    if (allPolygons.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void sukacheva::commandCount(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > commandKey;
  commandKey["EVEN"] = std::bind(countEvenVertices, _1, _2);
  commandKey["ODD"] = std::bind(countOddVertices, _1, _2);
  std::string command;
  in >> command;
  try
  {
    commandKey.at(command)(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    if (!std::isalpha(command[0]))
    {
      size_t vertices = std::stoull(command);
      if (vertices < 3)
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
      countVertices(allPolygons, out, vertices);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}

bool sukacheva::isRectangle(const Polygon& poly, size_t index)
{
  if (index == poly.points.size())
  {
    return (poly.points.size() == 4) &&
      (std::count(poly.points.begin(), poly.points.end(), poly.points[0]) == 1);
  }
  const Point& currentPoint = poly.points[index];
  bool allUniqueBefore = std::none_of
  (
    poly.points.begin(),
    poly.points.begin() + index,
    [&](const Point& applicant)
    {
      return applicant == currentPoint;
    }
  );
  return allUniqueBefore && isRectangle(poly, index + 1);
}

void sukacheva::isRects(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  size_t count = std::count_if
  (
    allPolygons.begin(),
    allPolygons.end(),
    [](const Polygon& applicant)
    {
      return isRectangle(applicant, 0);
    }
  );
  out << std::fixed << count << '\n';
}

void sukacheva::commandRects(const std::vector<Polygon>& allPolygons, std::ostream& out)
{
  try
  {
    isRects(allPolygons, out);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

bool sukacheva::arePolygonsSame(const Polygon& applicant, const Polygon& overlay, size_t index)
{
  if (index == applicant.points.size())
  {
    return true;
  }
  const Point& point1 = applicant.points[index];
  const Point& point2 = overlay.points[index];
  if (point1 != point2)
  {
    return false;
  }
  return arePolygonsSame(applicant, overlay, index + 1);
}

size_t sukacheva::countSamePolygons(const std::vector<Polygon>& polygons, const Polygon& overlay, size_t index)
{
  if (index == polygons.size())
  {
    return 0;
  }
  const Polygon& currentPolygon = polygons[index];
  bool isSame = arePolygonsSame(currentPolygon, overlay, 0);
  return (isSame ? 1 : 0) + countSamePolygons(polygons, overlay, index + 1);
}

void sukacheva::commandSame(const std::vector<Polygon>& allPolygons, std::istream& in, std::ostream& out)
{
  Polygon overlay;
  in >> overlay;
  if (in.fail())
  {
    throw std::logic_error("< WRONG INPUT >\n");
  }
  try
  {
    out << countSamePolygons(allPolygons, overlay, 0);
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

