#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include "polygon.hpp"

namespace panov 
{
	std::vector<Polygon> parsePolygonsFromFile(const std::string& filename);
}

#endif
