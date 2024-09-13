#ifndef POLYGONS_COLLECTION_HPP
#define POLYGONS_COLLECTION_HPP

#include "polygon.hpp"

class PolygonsCollection {
public:
    PolygonsCollection();
    ~PolygonsCollection();

    void addPolygon(const Polygon& polygon);
    int countPermutations(const Polygon& target) const;
    int countRectangles() const;

    // Дополнительные функции
    double totalArea() const;
    double maxArea() const;
    double minArea() const;
    int countPolygonsWithVertexes(int vertexCount) const;

private:
    Polygon* polygons;
    int size;
    int capacity;

    void resize();
};

#endif 