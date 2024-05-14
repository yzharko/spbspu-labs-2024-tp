#include "Commands.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include "ScopeGuard.hpp"

double reznikova::getArea(const reznikova::Polygon & polygon)
{
  std::vector< double > sum;
  std::transform(
    polygon.points.begin(),
    polygon.points.end() - 1,
    std::next(polygon.points.begin()),
    std::back_inserter(sum),
    [](const Point & a, const Point & b)
    {
      return a.x * b.y - a.y * b.x;
    }
  );
  sum.push_back(polygon.points.back().x * polygon.points.front().y - polygon.points.back().y * polygon.points.front().x);
  double area = std::accumulate(sum.begin(), sum.end(), 0) * 0.5;
  return area;
}

size_t reznikova::getNumOfVertexes(const reznikova::Polygon & polygon)
{
  return polygon.points.size();
}


std::vector< reznikova::Polygon > reznikova::chooseOddPolygons(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< Polygon > odd_polygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(odd_polygons),
    [](const Polygon & polygon)
    {
      return (polygon.points.size() % 2 != 0);
    }
  );
  return odd_polygons;
}

std::vector< reznikova::Polygon > reznikova::chooseEvenPolygons(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< Polygon > even_polygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(even_polygons),
    [](const Polygon & polygon)
    {
      return (polygon.points.size() % 2 == 0);
    }
  );
  return even_polygons;
}

bool reznikova::checkIfSame(size_t num, const reznikova::Polygon & polygon)
{
  return (polygon.points.size() == num);
}

std::vector< reznikova::Polygon > reznikova::chooseNumPolygons(const std::vector< reznikova::Polygon > & polygons, size_t num)
{
  std::vector< Polygon > num_polygons;
  using namespace std::placeholders;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(num_polygons),
    std::bind(checkIfSame, num, _1)
  );
  return num_polygons;
}

std::vector< double > reznikova::getAllAreas(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< double > all_areas;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(all_areas),
    [](const Polygon & polygon)
    {
      return getArea(polygon);
    }
  );
  return all_areas;
}

std::vector< size_t > reznikova::getAllVertexes(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< size_t > all_vertexes;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(all_vertexes),
    [](const Polygon & polygon)
    {
      return getNumOfVertexes(polygon);
    }
  );
  return all_vertexes;
}

double reznikova::getSumArea(const std::vector< reznikova::Polygon > & polygons)
{
  std::vector< double > all_areas = getAllAreas(polygons);
  return std::accumulate(all_areas.begin(), all_areas.end(), 0.0);
}

void reznikova::areaCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string sub_command;
  is >> sub_command;
  out << std::fixed << std::setprecision(1);
  if (sub_command == "ODD")
  {
    std::vector< Polygon > odd_polygons = chooseOddPolygons(polygons);
    out << getSumArea(odd_polygons) << "\n";
  }
  else if (sub_command == "EVEN")
  {
    std::vector< Polygon > even_polygons = chooseEvenPolygons(polygons);
    out << getSumArea(even_polygons) << "\n";
  }
  else if (sub_command == "MEAN")
  {
    out << getSumArea(polygons)/polygons.size() << "\n";
  }
  else if (!std::isalpha(sub_command[0]) && stoull(sub_command) > 2)
  {
    std::vector< Polygon > num_polygons = chooseNumPolygons(polygons, size_t(stoull(sub_command)));
    out << getSumArea(num_polygons) << "\n";
  }
  else
  {
    throw std::runtime_error("wrong area parameter");
  }
}

void reznikova::maxCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string sub_command;
  is >> sub_command;
  out << std::fixed;
  if (sub_command == "AREA")
  {
    std::vector< double > all_areas = getAllAreas(polygons);
    out << std::setprecision(1) << *std::max_element(all_areas.begin(), all_areas.end());
  }
  else if (sub_command == "VERTEXES")
  {
    std::vector< size_t > all_areas = getAllVertexes(polygons);
    out << *std::max_element(all_areas.begin(), all_areas.end());
  }
  else
  {
    throw std::runtime_error("wrong max parameter");
  }
}

void reznikova::minCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string sub_command;
  is >> sub_command;
  out << std::fixed;
  if (sub_command == "AREA")
  {
    std::vector< double > all_areas = getAllAreas(polygons);
    out << std::setprecision(1) << *std::min_element(all_areas.begin(), all_areas.end());
  }
  else if (sub_command == "VERTEXES")
  {
    std::vector< size_t > all_areas = getAllVertexes(polygons);
    out << *std::min_element(all_areas.begin(), all_areas.end());
  }
  else
  {
    throw std::runtime_error("wrong max parameter");
  }
}

void reznikova::countCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::string sub_command;
  is >> sub_command;
  out << std::fixed;
  if (sub_command == "EVEN")
  {
    auto num_even_polygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      [](const Polygon & polygon)
      {
        return (polygon.points.size() % 2 == 0);
      }
    );
    out << num_even_polygons << "\n";
  }
  else if (sub_command == "ODD")
  {
    auto num_odd_polygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      [](const Polygon & polygon)
      {
        return (polygon.points.size() % 2 != 0);
      }
    );
    out << num_odd_polygons << "\n";
  }
  else if (!std::isalpha(sub_command[0]) && stoull(sub_command) > 2)
  {
    using namespace std::placeholders;
    auto num_same_vertex_polygons = std::count_if(
      polygons.begin(),
      polygons.end(),
      std::bind(checkIfSame, size_t(std::stoull(sub_command)), _1)
    );
    out << num_same_vertex_polygons << "\n";
  }
  else
  {
    throw std::runtime_error("wrong max parameter");
  }
}

bool reznikova::checkIfPointsEqual(const reznikova::Point & point, const reznikova::Polygon & polygon)
{
  auto num_of_perms = std::count_if(
    polygon.points.begin(),
    polygon.points.end(),
    [point](const Point & comp_point)
    {
      return (comp_point.x == point.x && comp_point.y == point.y) or (comp_point.y == point.x && comp_point.x == point.y);
    }
  );
  return (num_of_perms == 1);
}

bool reznikova::checkIfPerms(const reznikova::Polygon & base_polygon, const reznikova::Polygon & polygon)
{
  if (base_polygon.points.size() != polygon.points.size())
  {
    return false;
  }
    auto num_of_perms = std::count_if(
    base_polygon.points.begin(),
    base_polygon.points.end(),
    [polygon](const Point & cmp_point)
    {
      return checkIfPointsEqual(cmp_point, polygon);
    }
  );
  if (size_t(num_of_perms) == polygon.points.size())
  {
    return true;
  }
  return false;
}

void reznikova::permsCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out, std::istream & is)
{
  Polygon base_polygon;
  is >> base_polygon;
  out << std::fixed;
  using namespace std::placeholders;
  auto num_perms = std::count_if(
    polygons.begin(),
    polygons.end(),
    std::bind(checkIfPerms, base_polygon, _1)
  );
  out << num_perms << "\n";
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
      Point p1 = polygon.points[0];
      Point p2 = polygon.points[1];
      Point p3 = polygon.points[2];
      Point p4 = polygon.points[3];
      if (checkIfParallelogram(polygon))
      {
        return ((p2.x - p1.x) * (p2.x - p1.x) + (p4.y - p1.y) * (p4.y - p1.y)) == ((p3.y - p2.y) * (p3.y - p2.y) + (p3.x - p4.x) * (p3.x - p4.x));
      }
    }
    return false;
}

void reznikova::rectsCommand(const std::vector< reznikova::Polygon > & polygons, std::ostream & out)
{
  out << std::fixed;
  using namespace std::placeholders;
  auto num_rects = std::count_if(
    polygons.begin(),
    polygons.end(),
    [](const Polygon & polygon)
    {
      return checkIfRect(polygon);
    }
  );
  out << num_rects << "\n";
}
