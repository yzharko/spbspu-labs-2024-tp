#ifndef GEOMETRYUTILS_HPP
#define GEOMETRYUTILS_HPP

#include "Polygon.hpp"

double calculateArea(const Polygon& polygon);
double calculateAreaEvenOdd(bool even, const std::vector< Polygon >& polygons);
double calculateMeanArea(const std::vector< Polygon >& polygons);
double calculateAreaByVertexCount(int count, const std::vector< Polygon >& polygons);
double calculateMaxArea(const std::vector< Polygon >& polygons);
int calculateMaxVertexes(const std::vector< Polygon >& polygons);
double calculateMinArea(const std::vector< Polygon >& polygons);
int calculateMinVertexes(const std::vector< Polygon >& polygons);
int countPolygons(bool even, const std::vector< Polygon >& polygons, int vertex_count = 0);
int countPerms(const Polygon& target, const std::vector< Polygon >& polygons);
int removeEcho(const Polygon& target, std::vector< Polygon >& polygons);

#endif
