#include "polygon.hpp"
#include <algorithm>
#include <cmath>

Polygon::Polygon() : points(nullptr), size(0) {}

Polygon::Polygon(Point* points, int size) : size(size) {
    this->points = new Point[size];
    for (int i = 0; i < size; ++i) {
        this->points[i] = points[i];
    }
}

Polygon::Polygon(const Polygon& other) {
    copyFrom(other);
}

Polygon& Polygon::operator=(const Polygon& other) {
    if (this != &other) {
        delete[] points;
        copyFrom(other);
    }
    return *this;
}

void Polygon::copyFrom(const Polygon& other) {
    size = other.size;
    points = new Point[size];
    for (int i = 0; i < size; ++i) {
        points[i] = other.points[i];
    }
}

Polygon::~Polygon() {
    delete[] points;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Polygon::isPermutation(const Polygon& other) const {
    if (size != other.size) {
        return false;
    }

    Point* sortedPoints = new Point[size];
    Point* sortedOtherPoints = new Point[other.size];

    std::copy(points, points + size, sortedPoints);
    std::copy(other.points, other.points + other.size, sortedOtherPoints);

    std::sort(sortedPoints, sortedPoints + size, [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    std::sort(sortedOtherPoints, sortedOtherPoints + other.size, [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    bool result = std::equal(sortedPoints, sortedPoints + size, sortedOtherPoints);

    delete[] sortedPoints;
    delete[] sortedOtherPoints;

    return result;
}

bool Polygon::isRectangle() const {
    if (size != 4) {
        return false;
    }
    int dx1 = std::abs(points[1].x - points[0].x);
    int dy1 = std::abs(points[1].y - points[0].y);
    int dx2 = std::abs(points[3].x - points[2].x);
    int dy2 = std::abs(points[3].y - points[2].y);
    return dx1 == dx2 && dy1 == dy2;
}

double Polygon::getArea() const {
    if (size < 3) return 0.0;

    double area = 0.0;
    for (int i = 0; i < size; ++i) {
        int j = (i + 1) % size;
        area += points[i].x * points[j].y;
        area -= points[j].x * points[i].y;
    }
    return std::abs(area) / 2.0;
}

int Polygon::getSize() const {
    return size;
}