#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

class Commands
{
public:
    explicit Commands(std::vector< Polygon >& polygons);

    void areaCommand(std::istream& input, std::ostream& output);
    void maxCommand(std::istream& input, std::ostream& output);
    void minCommand(std::istream& input, std::ostream& output);
    void countCommand(std::istream& input, std::ostream& output);
    void rmechoCommand(std::istream& input, std::ostream& output);
    void permsCommand(std::istream& input, std::ostream& output);

private:
    std::vector< Polygon >& polygons;

    double calculateAreaEvenOdd(bool even) const;
    double calculateMeanArea() const;
    double calculateAreaByVertexCount(int count) const;
    double calculateMaxArea() const;
    int calculateMaxVertexes() const;
    double calculateMinArea() const;
    int calculateMinVertexes() const;
    int countPolygons(bool even, int vertex_count = -1) const;
    int countPerms(const Polygon& target) const;
    int removeEcho(const Polygon& target);
};

#endif
