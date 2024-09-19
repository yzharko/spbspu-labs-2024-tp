#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace panov 
{
    std::vector<Polygon> parsePolygonsFromFile(const std::string& filename) 
    {
        std::vector<Polygon> polygons;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            Polygon polygon;
            size_t n;
            char ch;
            iss >> n;
            for (size_t i = 0; i < n; ++i) 
            {
                Point p;
                iss >> ch >> p.x >> ch >> p.y >> ch;
                polygon.points.push_back(p);
            }
            if (polygon.points.size() == n) 
            {
                polygons.push_back(polygon);
            }
        }
        return polygons;
    }
}
