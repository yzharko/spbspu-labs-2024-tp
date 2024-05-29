#ifndef GRAPHUTILS_HPP
#define GRAPHUTILS_HPP

#include <iosfwd>
#include <map>
#include "Graph.hpp"

void addVertex(Graph &graph, const std::string &vertex);
void addEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int weight);
void deleteVertex(Graph &graph, const std::string &vertex);
void deleteEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2);
void updateEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int newWeight);
void neighbors(const Graph &graph, const std::string &vertex, std::ostream &output);
void isConnected(const Graph &graph, const std::string &vertex1, const std::string &vertex2, std::ostream &output);

#endif
