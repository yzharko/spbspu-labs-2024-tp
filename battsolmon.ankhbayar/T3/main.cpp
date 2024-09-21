#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

};

struct Polygon {
    std::vector<Point> points;

    bool operator==(const Polygon& other) const {
        return points == other.points;
    }
};

std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int numPoints;
        if (iss >> numPoints) {
            Polygon polygon;
            for (int i = 0; i < numPoints; ++i) {
                Point p;
                char delimiter;
                if (iss >> delimiter >> p.x >> delimiter >> p.y >> delimiter) {
                    polygon.points.push_back(p);
                }
            }
            polygons.push_back(polygon);
        }
    }
    return polygons;
}

int removeConsecutiveDuplicates(std::vector<Polygon>& polygons, const Polygon& target) {
    auto it = std::unique(polygons.begin(), polygons.end(),
        [&target](const Polygon& a, const Polygon& b) {
            return a == target && b == target;
        });
    int removedCount = std::distance(it, polygons.end());
    polygons.erase(it, polygons.end());
    return removedCount;
}

int countRectangles(const std::vector<Polygon>& polygons) {
    return std::count_if(polygons.begin(), polygons.end(), [](const Polygon& p) {
        return p.points.size() == 4; // Простой критерий для прямоугольника
        });
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Ошибка: имя файла не задано." << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> polygons = readPolygonsFromFile(filename);
    std::string command;

    while (std::getline(std::cin, command)) {
        if (command.find("RMECHO") == 0) {
            std::istringstream iss(command);
            std::string cmd;
            int numPoints;
            Polygon target;
            iss >> cmd >> numPoints;
            for (int i = 0; i < numPoints; ++i) {
                Point p;
                char delimiter;
                iss >> delimiter >> p.x >> delimiter >> p.y >> delimiter;
                target.points.push_back(p);
            }
            int removed = removeConsecutiveDuplicates(polygons, target);
            std::cout << removed << std::endl;
        }
        else if (command == "RECTS") {
            int rectangleCount = countRectangles(polygons);
            std::cout << rectangleCount << std::endl;
        }
        else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    return 0;
}
