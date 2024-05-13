#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

class FileReader
{
public:
    std::vector< Polygon > readPolygons(const std::string& filename) const;
};

#endif
