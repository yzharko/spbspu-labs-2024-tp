#include "commands.hpp"
#include <fstream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iomanip>

std::ostream& psarev::chooseAreaType(std::vector< Polygon >& polyVec, std::istream& in, std::ostream& out)
{
  std::string type = "";
  in >> type;
  out << std::fixed << std::setprecision(1);

  if (type == "EVEN")
  {
    getEvenArea(polyVec, out);
  }
  //else if ()
  //{

  //}
  return out;
}

using namespace std::placeholders;

void psarev::getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out)
{
  std::cout << std::accumulate(polyVec.begin(), polyVec.end(), 0, std::bind(sumEvenAreas, _2, _1)) << '\n';
}

//void psarev::areaMean(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA MEAN dispatched\n";
//}
//void psarev::areaNumOfVerts(int&, std::istream&, std::ostream& out)
//{
//  out << "AREA NOV dispatched\n";
//}