#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace panov
{
    int countPermutations(const std::vector<Polygon>& polygons, const Polygon& polygon);
    int echoPolygon(std::vector<Polygon>& polygons, const Polygon& polygon);

    double areaSum(const std::vector<Polygon>& polygons, bool even);
    double areaMean(const std::vector<Polygon>& polygons);
    double areaByVertexCount(const std::vector<Polygon>& polygons, size_t vertexCount);
    double maxArea(const std::vector<Polygon>& polygons);
    int maxVertexes(const std::vector<Polygon>& polygons);
    double minArea(const std::vector<Polygon>& polygons);
    int minVertexes(const std::vector<Polygon>& polygons);
    int countByVertexes(const std::vector<Polygon>& polygons, bool even, int vertexCount = -1);
}

#endif
