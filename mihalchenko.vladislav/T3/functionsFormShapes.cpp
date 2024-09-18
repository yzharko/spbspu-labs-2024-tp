#include "functionsFormShapes.hpp"
#include <iomanip>
#include <cmath>
#include <numeric>
#include <scopeGuard.hpp>

size_t mihalchenko::getSize(const Polygon &polygon)
{
  return polygon.points.size();
}

double mihalchenko::getPoints(const Point &first, const Point &second)
{
  return first.x * second.y - first.y * second.x;
}

double mihalchenko::countArea(const Polygon &polygon)
{
  using namespace std::placeholders;
  std::vector< double > vectorArea;
  std::transform(++polygon.points.cbegin(), polygon.points.cend(),
    polygon.points.cbegin(),
    std::back_inserter(vectorArea),
    std::bind(getPoints, _1, _2));
  double area = std::accumulate(vectorArea.cbegin(),
    vectorArea.cend(), 0.);
  auto lhs = polygon.points.begin()->x * polygon.points.back().y;
  auto rhs = polygon.points.back().x * polygon.points.begin()->y;
  auto pmArea = lhs - rhs;
  area = 0.5 * std::abs(area + pmArea);
  return area;
}

void mihalchenko::getAreaOdd(const std::vector< Polygon > &polygons, std::ostream &out)
{
  using namespace std::placeholders;
  std::vector< Polygon > copyOddPolygons;
  std::copy_if(polygons.cbegin(), polygons.cend(),
    std::back_inserter(copyOddPolygons),
    std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2));
  getAreaResult(copyOddPolygons, false, out);
}

void mihalchenko::getAreaEven(const std::vector< Polygon > &polygons, std::ostream &out)
{
  using namespace std::placeholders;
  std::vector< Polygon > copyEvenPolygons;
  std::copy_if(polygons.cbegin(),
    polygons.cend(),
    std::back_inserter(copyEvenPolygons),
    std::bind(std::logical_not< bool >{},
    std::bind(std::bind(std::modulus< size_t >{},
    std::bind(getSize, _1), 2), _1)));
  getAreaResult(copyEvenPolygons, false, out);
}

void mihalchenko::getAreaMean(const std::vector< Polygon > &polygons, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty data");
  }
  std::vector< Polygon > copyPolygons;
  std::copy(polygons.cbegin(),
    polygons.cend(),
    std::back_inserter(copyPolygons));
  getAreaResult(copyPolygons, true, out);
}

void mihalchenko::getAreaVertexes(const std::vector< Polygon > &polygons, size_t num, std::ostream &out)
{
  using namespace std::placeholders;
  std::vector< Polygon > copyPolygonIfEqual;
  std::copy_if(
    polygons.cbegin(),
    polygons.cend(),
    std::back_inserter(copyPolygonIfEqual),
    std::bind(std::bind(std::equal_to< size_t >{}, std::bind(getSize, _1), _2), _1, num));
  getAreaResult(copyPolygonIfEqual, false, out);
}

std::ostream &mihalchenko::getAreaResult(const std::vector< Polygon > &copyPolygons,
                                          bool isMeanPredicate, std::ostream &out)
{
  using namespace std::placeholders;
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  if (isMeanPredicate == false)
  {
    out << std::accumulate(copyPolygons.begin(),
      copyPolygons.end(), 0.,
      std::bind(std::plus< double >{}, _1, std::bind(countArea, _2)));
  }
  else
  {
    out << std::accumulate(copyPolygons.begin(),
      copyPolygons.end(), 0.,
      std::bind(std::plus< double >{}, _1,
      std::bind(countArea, _2))) / copyPolygons.size();
  }
  return out << '\n';
}

int mihalchenko::getNumOfVertexes(const Polygon &polygons)
{
  return polygons.points.size();
}

std::ostream &mihalchenko::getMaxArea(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), countArea);
  double maxArea = *std::max_element(areas.cbegin(), areas.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << maxArea << '\n';
  return out;
}

std::ostream &mihalchenko::getMaxVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< int > numsOfVertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::max_element(numsOfVertexes.cbegin(), numsOfVertexes.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << maxVertexes << '\n';
  return out;
}

std::ostream &mihalchenko::getMinArea(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), countArea);
  double maxArea = *std::min_element(areas.cbegin(), areas.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << maxArea << '\n';
  return out;
}

std::ostream &mihalchenko::getMinVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< int > numsOfVertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::min_element(numsOfVertexes.cbegin(), numsOfVertexes.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << maxVertexes << '\n';
  return out;
}

std::ostream &mihalchenko::countOdd(const std::vector< Polygon > &polygons, std::ostream &out)
{
  using namespace std::placeholders;
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << std::count_if(polygons.begin(),
    polygons.end(),
    std::bind(std::modulus< size_t >{}, std::bind(getSize, _1), 2)) << '\n';
  return out;
}

std::ostream &mihalchenko::countEven(const std::vector< Polygon > &polygons, std::ostream &out)
{
  using namespace std::placeholders;
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << std::count_if(polygons.begin(), polygons.end(),
    std::bind(std::logical_not< bool >{},
    std::bind(std::bind(std::modulus< size_t >{},
    std::bind(getSize, _1), 2), _1))) << '\n';
  return out;
}

std::ostream &mihalchenko::countVertexes(const std::vector< Polygon > &polygons, size_t num, std::ostream &out)
{
  using namespace std::placeholders;
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << std::count_if(polygons.begin(),
    polygons.end(),
    std::bind(std::bind(std::equal_to< size_t >{},
    std::bind(getSize, _1), _2), _1, num)) << '\n';
  return out;
}

long long mihalchenko::getLength(const Polygon &polygon)
{
  return polygon.points.size();
}

bool mihalchenko::isLengthCorrect(const Polygon &lhsPolygon, const Polygon &rhsPolygon)
{
  using namespace std::placeholders;
  if (getLength(lhsPolygon) == std::count_if(rhsPolygon.points.begin(),
    rhsPolygon.points.end(),
    std::bind(arePointsCorrect,
    lhsPolygon, _1)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool mihalchenko::isPointCorrect(const Point &lhsPoint, const Point &rhsPoint)
{
  if (((lhsPoint.x == rhsPoint.x) && (lhsPoint.y == rhsPoint.y)) ||
    ((lhsPoint.x == rhsPoint.y) && (lhsPoint.y == rhsPoint.x)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool mihalchenko::arePointsCorrect(const Polygon &polygon, const Point &point)
{
  using namespace std::placeholders;
  return std::find_if(polygon.points.begin(),
    polygon.points.end(),
    std::bind(isPointCorrect, point, _1)) != polygon.points.end();
}

mihalchenko::Point mihalchenko::getVector(const Point &lhsPoint, const Point &rhsPoint)
{
  return Point{rhsPoint.x - lhsPoint.x, rhsPoint.y - lhsPoint.y};
}

double mihalchenko::getCos(const Point &lhsVect, const Point &rhsVect)
{
  double scalarProduct = lhsVect.x * rhsVect.x + rhsVect.y * rhsVect.y;
  double lengthOfLhsVector = sqrt(pow(lhsVect.x, 2) + pow(lhsVect.y, 2));
  double lengthOfRhsVector = sqrt(pow(rhsVect.x, 2) + pow(rhsVect.y, 2));
  return scalarProduct / (lengthOfLhsVector * lengthOfRhsVector);
}

bool mihalchenko::isZeroCos(const double &cos)
{
  return cos == 0;
}

bool mihalchenko::isRightPolygon(const Polygon &polygon)
{
  using namespace std::placeholders;
  std::vector< Point > vectorOfPoints;
  std::transform(
    polygon.points.begin(),
    std::prev(polygon.points.end()),
    std::next(polygon.points.begin()),
    std::back_inserter(vectorOfPoints),
    std::bind(getVector, _1, _2));
  vectorOfPoints.push_back(std::bind(getVector, _1, _2)(polygon.points.back(), polygon.points.front()));
  std::vector< double > cosOfVectors;
  std::transform(
    vectorOfPoints.begin(),
    std::prev(vectorOfPoints.end()),
    std::next(vectorOfPoints.begin()),
    std::back_inserter(cosOfVectors),
    std::bind(getCos, _1, _2));
  cosOfVectors.push_back(std::bind(getCos, _1, _2)(vectorOfPoints.back(), vectorOfPoints.front()));
  return std::find_if(
    cosOfVectors.begin(),
    cosOfVectors.end(),
    isZeroCos) != cosOfVectors.end();
}
