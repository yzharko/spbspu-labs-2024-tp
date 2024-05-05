#include "commands.hpp"
#include <numeric>
#include <algorithm>
#include <functional>
#include <string>
#include <iomanip>

using namespace std::placeholders;

std::ostream & redko::countAreas(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes)
{
  std::string parameter = "";
  in >> parameter;
  out << std::fixed << std::setprecision(1);
  if (parameter == "EVEN")
  {
    out << countAreasEven(shapes) << '\n';
  }
  else if (parameter == "ODD")
  {
    out << countAreasOdd(shapes) << '\n';
  }
  else if (parameter == "MEAN")
  {
    out << countAreasMean(shapes) << '\n';
  }
  else
  {
    int numOfVertexes = std::stoi(parameter);
    if (numOfVertexes <= 2)
    {
      throw std::logic_error("wrong parameter");
    }
    out << countAreasVertexes(shapes, numOfVertexes) << '\n';
  }
  return out;
}

double redko::countAreasEven(const std::vector < Polygon > & shapes)
{
  return std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumAreasIfEven);
}

double redko::countAreasOdd(const std::vector < Polygon > & shapes)
{
  return std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumAreasIfOdd);
}

double redko::countAreasMean(const std::vector < Polygon > & shapes)
{
  if (shapes.empty())
  {
    throw std::logic_error("unable to process with empty data");
  }
  double areas = std::accumulate(shapes.cbegin(), shapes.cend(), 0, sumAreas);
  return areas / shapes.size();
}

double redko::countAreasVertexes(const std::vector < Polygon > & shapes, int numOfVertexes)
{
  return std::accumulate(shapes.cbegin(), shapes.cend(), 0, std::bind(sumAreasIfEqual, _1, _2, numOfVertexes));
}

std::ostream & redko::getMax(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes)
{
  if (shapes.empty())
  {
    throw std::logic_error("unable to process with empty data");
  }
  std::string parameter = "";
  in >> parameter;
  if (parameter == "AREA")
  {
    out << std::fixed << std::setprecision(1) << getMaxArea(shapes) << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0) << getMaxVertexes(shapes) << '\n';
  }
  else
  {
    throw std::logic_error("wrong parameter");
  }
  return out;
}

double redko::getMaxArea(const std::vector < Polygon > & shapes)
{
  std::vector< double > areas(shapes.size());
  std::transform(shapes.begin(), shapes.end(), areas.begin(), countArea);
  double maxArea = *std::max_element(areas.begin(), areas.end());
  return maxArea;
}

double redko::getMaxVertexes(const std::vector < Polygon > & shapes)
{
  std::vector< int > numsOfVertexes(shapes.size());
  std::transform(shapes.begin(), shapes.end(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::max_element(numsOfVertexes.begin(), numsOfVertexes.end());
  return maxVertexes;
}

std::ostream & redko::getMin(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes)
{
  if (shapes.empty())
  {
    throw std::logic_error("unable to process with empty data");
  }
  std::string parameter = "";
  in >> parameter;
  if (parameter == "AREA")
  {
    out << std::fixed << std::setprecision(1) << getMinArea(shapes) << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    out << std::fixed << std::setprecision(0) << getMinVertexes(shapes) << '\n';
  }
  else
  {
    throw std::logic_error("wrong parameter");
  }
  return out;
}

double redko::getMinArea(const std::vector< Polygon > & shapes)
{
  std::vector< double > areas(shapes.size());
  std::transform(shapes.begin(), shapes.end(), areas.begin(), countArea);
  double minArea = *std::min_element(areas.begin(), areas.end());
  return minArea;
}

double redko::getMinVertexes(const std::vector< Polygon > & shapes)
{
  std::vector< int > numsOfVertexes(shapes.size());
  std::transform(shapes.cbegin(), shapes.cend(), numsOfVertexes.begin(), getNumOfVertexes);
  int minVertexes = *std::min_element(numsOfVertexes.begin(), numsOfVertexes.end());
  return minVertexes;
}

std::ostream & redko::count(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes)
{
  std::string parameter = "";
  in >> parameter;
  if (parameter == "EVEN")
  {
    out << countEven(shapes) << '\n';
  }
  else if (parameter == "ODD")
  {
    out << countOdd(shapes) << '\n';
  }
  else
  {
    int numOfVertexes = std::stoi(parameter);
    if (numOfVertexes <= 2)
    {
      throw std::logic_error("wrong parameter");
    }
    out << countShapes(shapes, numOfVertexes) << '\n';
  }
  return out;
}

int redko::countEven(const std::vector < Polygon > & shapes)
{
  return std::count_if(shapes.begin(), shapes.end(), isNumOfVertexesEven);
}

int redko::countOdd(const std::vector < Polygon > & shapes)
{
  return std::count_if(shapes.begin(), shapes.end(), isNumOfVertexesOdd);
}

int redko::countShapes(const std::vector < Polygon > & shapes, int numOfVertexes)
{
  return std::count_if(shapes.begin(), shapes.end(), std::bind(isNumOfVertexesEqual, _1, numOfVertexes));
}

std::ostream & redko::countIntersections(std::istream & in, std::ostream & out, const std::vector < Polygon > & shapes)
{
  Polygon compairingShape{};
  if (!(in >> compairingShape))
  {
    throw std::logic_error("wrong parameter");
  }
  out << std::count_if(shapes.begin(), shapes.end(), std::bind(isIntersected, _1, compairingShape)) << '\n';
  return out;
}

std::ostream & redko::countRightShapes(std::istream &, std::ostream & out, const std::vector < Polygon > & shapes)
{
  out << std::count_if(shapes.cbegin(), shapes.cend(), isRightShape) << '\n';
  return out;
}

std::ostream & redko::printMessage(std::ostream & out, const std::string & message)
{
  out << message << '\n';
  return out;
}
