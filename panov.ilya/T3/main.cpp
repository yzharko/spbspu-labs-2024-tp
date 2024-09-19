#include <iostream>
#include <vector>
#include <string>
#include "polygon.hpp"
#include "parser.hpp"
#include "commands.hpp"
#include <iomanip>

namespace panov
{
    void handleCommands(std::vector<Polygon>& polygons)
    {
        std::string command;
        while (std::cin >> command)
        {
            if (command == "PERMS")
            {
                Polygon polygon;
                int n;
                std::cin >> n;
                char ch;
                for (int i = 0; i < n; ++i)
                {
                    Point p;
                    std::cin >> ch >> p.x >> ch >> p.y >> ch;
                    polygon.points.push_back(p);
                }
                std::cout << countPermutations(polygons, polygon) << std::endl;
            }
            else if (command == "ECHO")
            {
                Polygon polygon;
                int n;
                std::cin >> n;
                char ch;
                for (int i = 0; i < n; ++i)
                {
                    Point p;
                    std::cin >> ch >> p.x >> ch >> p.y >> ch;
                    polygon.points.push_back(p);
                }
                std::cout << echoPolygon(polygons, polygon) << std::endl;
            }
            else if (command == "AREA")
            {
                std::string type;
                std::cin >> type;

                if (type == "EVEN" || type == "ODD")
                {
                    bool even = (type != "EVEN");
                    std::cout << std::fixed << std::setprecision(1) << areaSum(polygons, even) << std::endl;
                }
                else if (type == "MEAN")
                {
                    std::cout << std::fixed << std::setprecision(1) << areaMean(polygons) << std::endl;
                }
                else
                {
                    size_t vertexCount = std::stoi(type);
                    std::cout << std::fixed << std::setprecision(1) << areaByVertexCount(polygons, vertexCount) << std::endl;
                }
            }
            else if (command == "MAX")
            {
                std::string type;
                std::cin >> type;

                if (type == "AREA")
                {
                    std::cout << std::fixed << std::setprecision(1) << maxArea(polygons) << std::endl;
                }
                else if (type == "VERTEXES")
                {
                    std::cout << maxVertexes(polygons) << std::endl;
                }
            }
            else if (command == "MIN")
            {
                std::string type;
                std::cin >> type;

                if (type == "AREA")
                {
                    std::cout << std::fixed << std::setprecision(1) << minArea(polygons) << std::endl;
                }
                else if (type == "VERTEXES")
                {
                    std::cout << minVertexes(polygons) << std::endl;
                }
            }
            else if (command == "COUNT")
            {
                std::string type;
                std::cin >> type;

                if (type == "EVEN" || type == "ODD")
                {
                    bool even = (type == "EVEN");
                    std::cout << countByVertexes(polygons, even) << std::endl;
                }
                else
                {
                    int vertexCount = std::stoi(type);
                    std::cout << countByVertexes(polygons, false, vertexCount) << std::endl;
                }
            }
            else
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Filename not provided." << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<panov::Polygon> polygons = panov::parsePolygonsFromFile(filename);

    panov::handleCommands(polygons);

    return 0;
}
