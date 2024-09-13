#include "polygons_collection.hpp"

PolygonsCollection::PolygonsCollection() : size(0), capacity(2) {
    polygons = new Polygon[capacity];
}

PolygonsCollection::~PolygonsCollection() {
    delete[] polygons;
}

void PolygonsCollection::resize() {
    capacity *= 2;
    Polygon* newPolygons = new Polygon[capacity];
    for (int i = 0; i < size; ++i) {
        newPolygons[i] = polygons[i];
    }
    delete[] polygons;
    polygons = newPolygons;
}

void PolygonsCollection::addPolygon(const Polygon& polygon) {
    if (size >= capacity) {
        resize();
    }
    polygons[size++] = polygon;
}

int PolygonsCollection::countPermutations(const Polygon& target) const {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (polygons[i].isPermutation(target)) {
            ++count;
        }
    }
    return count;
}

int PolygonsCollection::countRectangles() const {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (polygons[i].isRectangle()) {
            ++count;
        }
    }
    return count;
}

double PolygonsCollection::totalArea() const {
    double totalArea = 0.0;
    for (int i = 0; i < size; ++i) {
        totalArea += polygons[i].getArea();
    }
    return totalArea;
}

double PolygonsCollection::maxArea() const {
    double maxArea = 0.0;
    for (int i = 0; i < size; ++i) {
        double area = polygons[i].getArea();
        if (area > maxArea) {
            maxArea = area;
        }
    }
    return maxArea;
}

double PolygonsCollection::minArea() const {
    if (size == 0) return 0.0;

    double minArea = polygons[0].getArea();
    for (int i = 1; i < size; ++i) {
        double area = polygons[i].getArea();
        if (area < minArea) {
            minArea = area;
        }
    }
    return minArea;
}

int PolygonsCollection::countPolygonsWithVertexes(int vertexCount) const {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (polygons[i].getSize() == vertexCount) {
            ++count;
        }
    }
    return count;
}