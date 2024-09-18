#include <iostream>
#include <algorithm>
#include <vector>
#include <iofmtguard.hpp>
#include "GraphUtils.hpp"

void addVertex(Graph &graph, const std::string &vertex) {
  if (graph.adjList.find(vertex) != graph.adjList.end()) {
    throw std::logic_error("Vertex already exists\n");
  }
  graph.adjList[vertex] = {};
}

void addEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int weight) {
  if (weight <= 0) {
    throw std::logic_error("Invalid edge weight\n");
  }
  if (graph.adjList.find(vertex1) == graph.adjList.end() || graph.adjList.find(vertex2) == graph.adjList.end()) {
    throw std::logic_error("One or both vertices do not exist\n");
  }
  if (graph.adjList[vertex1].find(vertex2) != graph.adjList[vertex1].end()) {
    throw std::logic_error("Edge already exists\n");
  }
  graph.adjList[vertex1][vertex2] = weight;
  graph.adjList[vertex2][vertex1] = weight;
}

void deleteVertex(Graph &graph, const std::string &vertex) {
  if (graph.adjList.find(vertex) == graph.adjList.end()) {
    throw std::logic_error("Vertex does not exist\n");
  }
  graph.adjList.erase(vertex);
  for (auto &keyEdgesPair: graph.adjList) {
    auto &edges = keyEdgesPair.second;
    edges.erase(vertex);
  }
}

void deleteEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2) {
  if (graph.adjList.find(vertex1) == graph.adjList.end() || graph.adjList.find(vertex2) == graph.adjList.end()) {
    throw std::logic_error("One of the vertex does not exist\n");
  }
  if (graph.adjList[vertex1].find(vertex2) == graph.adjList[vertex1].end()) {
    throw std::logic_error("Edge does not exist\n");
  }
  graph.adjList[vertex1].erase(vertex2);
  graph.adjList[vertex2].erase(vertex1);
}

void updateEdge(Graph &graph, const std::string &vertex1, const std::string &vertex2, int newWeight) {
  if (newWeight <= 0) {
    throw std::logic_error("Invalid edge weight\n");
  }
  if (graph.adjList[vertex1].find(vertex2) == graph.adjList[vertex1].end()) {
    throw std::logic_error("Edge not found\n");
  }
  graph.adjList[vertex1][vertex2] = newWeight;
  graph.adjList[vertex2][vertex1] = newWeight;
}

void neighbors(const Graph &graph, const std::string &vertex, std::ostream &output) {
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (graph.adjList.find(vertex) == graph.adjList.end()) {
    throw std::logic_error("Vertex does not exist\n");
  }
  const auto &edges = graph.adjList.at(vertex);
  for (const auto &neighborWeightPair: edges) {
    const auto &neighbor = neighborWeightPair.first;
    const auto &weight = neighborWeightPair.second;
    output << "(" << neighbor << ", " << weight << ") ";
  }
  output << "\n";
}

void isConnected(const Graph &graph, const std::string &vertex1, const std::string &vertex2, std::ostream &output) {
  if (graph.adjList.find(vertex1) == graph.adjList.end() || graph.adjList.find(vertex2) == graph.adjList.end()) {
    throw std::logic_error("One or both vertices do not exist\n");
  }

  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  std::vector< std::string > visited;
  std::vector< std::string > stack = {vertex1};
  while (!stack.empty()) {
    std::string current = stack.back();
    stack.pop_back();
    if (current == vertex2) {
      output << "Connected\n";
    }
    else {
      if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
        visited.push_back(current);
        for (const auto &neighborWeightPair: graph.adjList.at(current)) {
          const auto &neighbor = neighborWeightPair.first;
          stack.push_back(neighbor);
        }
      }
    }
  }
  output << "Not connected\n";
}
