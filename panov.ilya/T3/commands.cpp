#include "commands.hpp"
#include <algorithm>
#include <iostream>
#include <functional>

namespace panov
{
    bool checkPointsEquality(const Point &point, const Polygon &polygon)
    {
        size_t permsCount = std::count_if(
            polygon.points.begin(),
            polygon.points.end(),
            [point](const Point &cmpPoint)
            {
                return (cmpPoint.x == point.x && cmpPoint.y == point.y) || (cmpPoint.y == point.x && cmpPoint.x == point.y);
            }
        );
        return permsCount >= 1;
    }

    bool checkPermutations(const Polygon &basePolygon, const Polygon &polygon)
    {
        if (basePolygon.points.size() != polygon.points.size())
        {
            return false;
        }

        size_t numOfPerms = std::count_if(
            basePolygon.points.begin(),
            basePolygon.points.end(),
            [polygon](const Point &cmpPoint)
            {
                return checkPointsEquality(cmpPoint, polygon);
            }
        );
        return numOfPerms == polygon.points.size();
    }

    int countPermutations(const std::vector<Polygon> &polygons, const Polygon &polygon)
    {
        using namespace std::placeholders;
        int numPerms = std::count_if(
            polygons.begin(),
            polygons.end(),
            std::bind(checkPermutations, polygon, _1)
        );
        return numPerms;
    }

    int echoPolygon(std::vector<Polygon> &polygons, const Polygon &polygon)
    {
        auto it = polygons.begin();
        int count = 0;
        while ((it = std::find(it, polygons.end(), polygon)) != polygons.end())
        {
            it = polygons.insert(it + 1, polygon);
            ++count;
            ++it;
        }
        return count;
    }

    double areaSum(const std::vector<Polygon> &polygons, bool even)
    {
        double totalArea = 0.0;
        for (const auto &poly : polygons)
        {
            if ((poly.points.size() % 2 == 0 && even) || (poly.points.size() % 2 != 0 && !even))
            {
                totalArea += poly.area();
            }
        }
        return totalArea;
    }

    double areaMean(const std::vector<Polygon> &polygons)
    {
        double totalArea = 0.0;
        for (const auto &poly : polygons)
        {
            totalArea += poly.area();
        }
        return polygons.empty() ? 0.0 : totalArea / polygons.size();
    }

    double areaByVertexCount(const std::vector<Polygon> &polygons, size_t vertexCount)
    {
        double totalArea = 0.0;
        for (const auto &poly : polygons)
        {
            if (poly.points.size() == vertexCount)
            {
                totalArea += poly.area();
            }
        }
        return totalArea;
    }

    double maxArea(const std::vector<Polygon> &polygons)
    {
        return std::max_element(polygons.begin(), polygons.end(),
                                [](const Polygon &a, const Polygon &b)
                                {
                                    return a.area() < b.area();
                                })
            ->area();
    }

    int maxVertexes(const std::vector<Polygon> &polygons)
    {
        return std::max_element(polygons.begin(), polygons.end(),
                                [](const Polygon &a, const Polygon &b)
                                {
                                    return a.points.size() < b.points.size();
                                })
            ->points.size();
    }

    double minArea(const std::vector<Polygon> &polygons)
    {
        return std::min_element(polygons.begin(), polygons.end(),
                                [](const Polygon &a, const Polygon &b)
                                {
                                    return a.area() < b.area();
                                })
            ->area();
    }

    int minVertexes(const std::vector<Polygon> &polygons)
    {
        return std::min_element(polygons.begin(), polygons.end(),
                                [](const Polygon &a, const Polygon &b)
                                {
                                    return a.points.size() < b.points.size();
                                })
            ->points.size();
    }

    int countByVertexes(const std::vector<Polygon> &polygons, bool even, int vertexCount)
    {
        if (vertexCount != -1)
        {
            return std::count_if(polygons.begin(), polygons.end(),
                                 [vertexCount](const Polygon &poly)
                                 {
                                     return poly.points.size() == static_cast<size_t>(vertexCount);
                                 });
        }
        return std::count_if(polygons.begin(), polygons.end(),
                             [even](const Polygon &poly)
                             {
                                 return (poly.points.size() % 2 == 0 && even) || (poly.points.size() % 2 != 0 && !even);
                             });
    }
}
