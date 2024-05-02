#include "commands.hpp"
#include <fstream>

void psarev::areaOdd(Polygon& pol, std::istream&, std::ostream& out)
{
  out << "AREA ODD dispatched\n";
  out << pol.points[0].x <<"\n";
}
void psarev::areaEven(int&, std::istream&, std::ostream& out)
{
  out << "AREA EVEN dispatched\n";
}
void psarev::areaMean(int&, std::istream&, std::ostream& out)
{
  out << "AREA MEAN dispatched\n";
}
void psarev::areaNumOfVerts(int&, std::istream&, std::ostream& out)
{
  out << "AREA NOV dispatched\n";
}