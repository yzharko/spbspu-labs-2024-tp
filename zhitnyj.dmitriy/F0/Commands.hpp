#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <string>
#include "Graph.hpp"

void printInvalidCommand(std::ostream &output);
void dijkstraCommand(std::istream &input, std::ostream &output, Graph &graph);
void shortestPathCommand(std::istream &input, std::ostream &output, const Graph &graph);
void saveGraphCommand(std::istream &input, std::ostream &output, const Graph &graph);
void loadGraphCommand(std::istream &input, std::ostream &output, Graph &graph);
void addCommand(std::istream &input, std::ostream &output, Graph &graph);
void delCommand(std::istream &input, std::ostream &output, Graph &graph);
void showGraphCommand(std::ostream &output, const Graph &graph);
void updateEdgeCommand(std::istream &input, std::ostream &output, Graph &graph);
void neighborsCommand(std::istream &input, std::ostream &output, const Graph &graph);
void isConnectedCommand(std::istream &input, std::ostream &output, const Graph &graph);
void helpCommand(std::ostream &output);

#endif
