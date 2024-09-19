#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygon.hpp"
#include <string>

namespace hohlova
{
  void Error(std::ostream& out);
  double CalcArea(const Polygon& polygon);
  unsigned long long int countVertices(const Polygon& polygon);

  void AREACommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void AREACommandEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void AREACommandOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void AREACommandMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void AREACommandNumVertices(const std::vector< Polygon >& polygons, unsigned long long numVertices, std::ostream& out);

  void MAXCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void MAXCommandArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void MAXCommandVertices(const std::vector< Polygon >& polygons, std::ostream& out);

  void MINCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void MINCommandArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void MINCommandVertices(const std::vector< Polygon >& polygons, std::ostream& out);

  void COUNTCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void COUNTCommandOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void COUNTCommandEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void COUNTCommandNumVertices(const std::vector< Polygon >& polygons, unsigned long long numVertices, std::ostream& out);

  void PERMSCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  int PERMScount(const Polygon& polyg, const std::vector< Polygon >& polygons);

  void MAXSEQCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);

  void RIGHTSHAPESCommandMenu(const std::vector< Polygon >& polygons, std::ostream& out);
  int countRightShapes(const std::vector< Polygon >& polygons);
}

#endif
