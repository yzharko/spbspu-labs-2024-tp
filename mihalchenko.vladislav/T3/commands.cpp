#include "commands.hpp"
#include <iomanip>
#include <cmath>
#include <scopeGuard.hpp>

void mihalchenko::printArea(const std::vector< Polygon > &polygons, std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "EVEN")
  {
    getAreaEven(polygons, out);
  }
  else if (partOfCmd == "ODD")
  {
    getAreaOdd(polygons, out);
  }
  else if (partOfCmd == "MEAN")
  {
    getAreaMean(polygons, out);
  }
  else if (isdigit(partOfCmd[0]) && stoull(partOfCmd) >= 3)
  {
    getAreaVertexes(polygons, stoull(partOfCmd), out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

void mihalchenko::printMax(const std::vector< Polygon > &polygons, std::istream &is, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty data");
  }
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "AREA")
  {
    getMaxArea(polygons, out);
  }
  else if (partOfCmd == "VERTEXES")
  {
    getMaxVertexes(polygons, out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

void mihalchenko::printMin(const std::vector< Polygon > &polygons, std::istream &is, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty data");
  }
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "AREA")
  {
    getMinArea(polygons, out);
  }
  else if (partOfCmd == "VERTEXES")
  {
    getMinVertexes(polygons, out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

void mihalchenko::printCount(const std::vector< Polygon > &polygons, std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "EVEN")
  {
    countEven(polygons, out);
  }
  else if (partOfCmd == "ODD")
  {
    countOdd(polygons, out);
  }
  else if ((partOfCmd[0]) && stoull(partOfCmd) >= 3)
  {
    countVertexes(polygons, stoull(partOfCmd), out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

void mihalchenko::printPerms(const std::vector< Polygon > &polygons, std::istream &is, std::ostream &out)
{
  using namespace std::placeholders;
  Polygon copyPolygon;
  is >> copyPolygon;
  long long numOfVertexes = copyPolygon.points.size();
  using namespace std::placeholders;
  std::vector< Polygon > copyVectorOfPolygons;
  copy_if(polygons.begin(),
    polygons.end(),
    std::back_inserter(copyVectorOfPolygons),
    std::bind(std::equal_to< long long >{},
    std::bind(getLength, _1), numOfVertexes));
  if (!copyVectorOfPolygons.empty())
  {
    iofmtguard fmtguard(out);
    out << std::fixed << std::setprecision(0);
    out << std::count_if(polygons.begin(),
      polygons.end(),
      std::bind(isLengthCorrect, copyPolygon, _1)) << '\n';
  }
  else
  {
    printErrorMessage(out);
  }
}

void mihalchenko::printCountRightShapes(const std::vector< Polygon > &polygons, std::istream &, std::ostream &out)
{
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(0);
  out << std::count_if(polygons.begin(), polygons.end(), isRightPolygon) + 1 << '\n';
}

std::ostream &mihalchenko::printErrorMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>" << '\n';
  return out;
}
