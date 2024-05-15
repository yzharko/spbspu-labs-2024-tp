#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

void printInvalidCommand(std::ostream& out);
void areaCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons);
void maxCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons);
void minCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons);
void countCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons);
void rmechoCommand(std::istream& input, std::ostream& output, std::vector< Polygon >& polygons);
void permsCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons);

#endif
