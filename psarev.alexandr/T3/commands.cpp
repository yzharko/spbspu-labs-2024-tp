#include "commands.hpp"
#include "checkFuncs.hpp"
#include <fstream>
#include <functional>
#include <numeric>

std::ostream& psarev::chooseAreaType(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string type = "";
  in >> type;
  if (type == "EVEN")
  {
    getEvenArea(polyVec, out);
  }
  //else if ()
  //{

  //}
}
double psarev::getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  double sumAreas = (polyVec.points.size() % 2 == 0) ? res + countArea(shape) : res;
  double result = std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(sumAreasIfEven, _1, _2));
}

//void psarev::areaMean(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA MEAN dispatched\n";
//}
//void psarev::areaNumOfVerts(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA NOV dispatched\n";
//}