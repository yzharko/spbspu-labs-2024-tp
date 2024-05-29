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
  for (auto &[key, edges]: graph.adjList) {
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

void showGraph(const Graph &graph) {
  for (const auto &[vertex, edges]: graph.adjList) {
    std::cout << vertex << ": ";
    for (const auto &[neighbor, weight]: edges) {
      std::cout << "(" << neighbor << ", " << weight << ") ";
    }
    std::cout << "\n";
  }
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

void neighbors(const Graph &graph, const std::string &vertex) {
  if (graph.adjList.find(vertex) == graph.adjList.end()) {
    throw std::logic_error("Vertex does not exist\n");
  }
  for (const auto &[neighbor, weight]: graph.adjList.at(vertex)) {
    std::cout << neighbor << " ";
  }
  std::cout << "\n";
}

void isConnected(const Graph &graph, const std::string &vertex1, const std::string &vertex2) {
  if (graph.adjList.find(vertex1) == graph.adjList.end() || graph.adjList.find(vertex2) == graph.adjList.end()) {
    throw std::logic_error("One or both vertices do not exist\n");
  }

  std::vector< std::string > visited;
  std::vector< std::string > stack = {vertex1};

  while (!stack.empty()) {
    std::string current = stack.back();
    stack.pop_back();
    if (current == vertex2) {
      std::cout << "Connected\n";
      return;
    }
    if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
      visited.push_back(current);
      for (const auto &[neighbor, _]: graph.adjList.at(current)) {
        stack.push_back(neighbor);
      }
    }
  }
  std::cout << "Not connected\n";
}
