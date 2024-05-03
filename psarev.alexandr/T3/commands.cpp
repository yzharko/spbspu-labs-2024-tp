#include "commands.hpp"
#include <fstream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <string>

std::ostream& psarev::chooseAreaType(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string type = "";
  in >> type;
  out << std::fixed << std::setprecision(1);

  if (type == "EVEN")
  {
    getEvenArea(polyVec, out);
  }
  else if (type == "ODD")
  {
    getOddArea(polyVec, out);
  }
  else if (type == "MEAN")
  {
    getMeanArea(polyVec, out);
  }
  else
  {
    if (isDigit(type)) {
      size_t numOfVerts = std::stoi(type);
      getAreaNumOfVerts(polyVec, out, numOfVerts);
    }
    else
    {
      throw std::overflow_error("<INVALID COMMAND>");
    }
  }
  return out;
}

using namespace std::placeholders;

void psarev::getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  std::cout << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusEvenArea, _1, _2)) << '\n';
}

void psarev::getOddArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  std::cout << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusOddArea, _1, _2)) << '\n';
}

void psarev::getMeanArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  double areaSum = std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusArea, _1, _2)) << '\n';
  std::cout << areaSum / polyVec.size();
}

void psarev::getAreaNumOfVerts(std::vector< Polygon >& polyVec, std::ostream& out, size_t& numOfVerts)
{
  std::cout << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(plusSameArea, _1, _2, numOfVerts)) << '\n';
}

//void psarev::areaMean(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA MEAN dispatched\n";
//}
//void psarev::areaNumOfVerts(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA NOV dispatched\n";
//}