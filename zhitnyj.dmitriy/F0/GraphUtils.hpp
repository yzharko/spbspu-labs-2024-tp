#ifndef GRAPHUTILS_HPP
#define GRAPHUTILS_HPP

#include <iostream>
#include <map>
#include "Graph.hpp"

void addVertex(Graph &graph, const std::string &vertex);
void addEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int weight);
void deleteVertex(Graph &graph, const std::string &vertex);
void deleteEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2);
void showGraph(const Graph &graph);
void updateEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int newWeight);
void neighbors(const Graph &graph, const std::string &vertex);
void isConnected(const Graph &graph, const std::string &vertex1, const std::string &vertex2);

#endif
