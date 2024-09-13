#ifndef POLYGON_HPP
#define POLYGON_HPP

struct Point {
    int x, y;

    bool operator==(const Point& other) const;
};

class Polygon {
public:
    Polygon();
    Polygon(Point* points, int size);
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    ~Polygon();

    bool isPermutation(const Polygon& other) const;
    bool isRectangle() const;
    double getArea() const;
    int getSize() const;

private:
    Point* points;
    int size;

    void copyFrom(const Polygon& other);
};

#endif
