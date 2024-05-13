#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

class Commands
{
public:
    double calculateAreaEvenOdd(const std::vector< Polygon >& polygons, bool even) const;
    double calculateMeanArea(const std::vector< Polygon >& polygons) const;
    double calculateAreaByVertexCount(const std::vector< Polygon >& polygons, int count) const;
    double calculateMaxArea(const std::vector< Polygon >& polygons) const;
    int calculateMaxVertexes(const std::vector< Polygon >& polygons) const;
    double calculateMinArea(const std::vector< Polygon >& polygons) const;
    int calculateMinVertexes(const std::vector< Polygon >& polygons) const;
    int countPolygons(const std::vector< Polygon >& polygons, bool even, int vertex_count = -1) const;
    int countPerms(const std::vector< Polygon >& polygons, const Polygon& target) const;
    int removeEcho(std::vector< Polygon >& polygons, const Polygon& target) const;
};

#endif // COMMANDS_HPP
