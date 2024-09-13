#include <iostream>
#include <fstream>
#include "polygon.hpp"
#include "polygons_collection.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    PolygonsCollection collection;

    int numPoints;
    while (file >> numPoints) {
        Point* points = new Point[numPoints];
        for (int i = 0; i < numPoints; ++i) {
            file >> points[i].x >> points[i].y;
        }
        Polygon polygon(points, numPoints);
        collection.addPolygon(polygon);
        delete[] points;
    }

    Point targetPoints[] = { {0, 0}, {2, 2}, {2, 0}, {0, 2} };
    Polygon targetPolygon(targetPoints, 4);

    int permsCount = collection.countPermutations(targetPolygon);
    std::cout << "PERMS: " << permsCount << std::endl;

    int rectsCount = collection.countRectangles();
    std::cout << "RECTS: " << rectsCount << std::endl;

    double totalArea = collection.totalArea();
    std::cout << "Total Area: " << totalArea << std::endl;

    double maxArea = collection.maxArea();
    std::cout << "Max Area: " << maxArea << std::endl;

    double minArea = collection.minArea();
    std::cout << "Min Area: " << minArea << std::endl;

    int polygonsWith3Vertices = collection.countPolygonsWithVertexes(3);
    std::cout << "Polygons with 3 vertices: " << polygonsWith3Vertices << std::endl;

    return 0;
}
