#include "myAlgorithms.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

bool anikanov::checkMatrix(const std::vector< std::vector< int > > &matrix)
{
  int n = matrix.size();

  for (int i = 0; i < n; ++i) {
    if (matrix[i][i] != 0) {
      return false;
    }
    for (int j = 0; j < i; ++j) {
      if (matrix[i][j] < 0 || matrix[j][i] < 0) {
        return false;
      }
      if (matrix[i][j] != matrix[j][i]) {
        return false;
      }
    }
  }

  return true;
}

std::vector< std::vector< int > > anikanov::getEdges(const std::vector< std::vector< int > > &graph)
{
  std::vector< std::vector< int > > edges;
  int n = graph.size();

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (graph[i][j] != 0) {
        edges.push_back(std::vector< int >{i, j, graph[i][j]});
      }
    }
  }

  return edges;
}

int anikanov::findParent(std::vector< int > &parent, int i)
{
  if (parent[i] != i) {
    parent[i] = findParent(parent, parent[i]);
  }
  return parent[i];
}

void anikanov::merge(std::vector< int > &parent, std::vector< int > &rank, int x, int y)
{
  int xroot = findParent(parent, x);
  int yroot = findParent(parent, y);

  if (rank[xroot] < rank[yroot]) {
    parent[xroot] = yroot;
  } else if (rank[xroot] > rank[yroot]) {
    parent[yroot] = xroot;
  } else {
    parent[yroot] = xroot;
    rank[xroot]++;
  }
}

std::vector< std::vector< int > > anikanov::runKruskalMST(std::vector< std::vector< int > > &edges, int V)
{
  std::vector< std::vector< int > > result;

  std::sort(edges.begin(), edges.end(), [](const std::vector< int > &a, const std::vector< int > &b) {
    return a[2] < b[2];
  });

  std::vector< int > parent(V);
  std::vector< int > rank(V, 0);

  for (int v = 0; v < V; ++v) {
    parent[v] = v;
  }

  for (const auto &edge: edges) {
    int x = findParent(parent, edge[0]);
    int y = findParent(parent, edge[1]);

    if (x != y) {
      result.push_back(edge);
      merge(parent, rank, x, y);
    }
  }

  return result;
}

int anikanov::findNumberOfVertices(const std::vector< std::vector< int > > &edges)
{
  std::vector< int > vertices;

  for (const auto &edge: edges) {
    vertices.push_back(edge[0]);
    vertices.push_back(edge[1]);
  }

  sort(vertices.begin(), vertices.end());
  vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

  return vertices.size();
}

std::vector< std::vector< int > > anikanov::toMatrix(const std::vector< std::vector< int > > &edges)
{
  int n = findNumberOfVertices(edges);
  std::vector< std::vector< int > > matrix(n, std::vector< int >(n, 0));

  for (const auto &edge: edges) {
    matrix[edge[0]][edge[1]] = edge[2];
    matrix[edge[1]][edge[0]] = edge[2];
  }

  return matrix;
}

void anikanov::printAns(const matrix_t &edges, const int sum, const std::shared_ptr< SceneManager > &manager)
{
  std::ostream *out = &manager->getOutputStream();
  std::ofstream fileOut;

  if (manager->getSettings().saveOutput) {
    fileOut = std::ofstream("out.txt");
    if (!fileOut.is_open()) {
      *out << "Error on opening file.\n";
      return;
    }
  }

  std::vector< std::vector< int > > toPrint = manager->getSettings().outputMatrix ? toMatrix(edges) : edges;

  for (const auto &row: toPrint) {
    for (const auto &elem: row) {
      *out << elem << " ";
      if (manager->getSettings().saveOutput) {
        fileOut << elem << " ";
      }
    }
    *out << "\n";
    if (manager->getSettings().saveOutput) {
      fileOut << "\n";
    }
  }

  *out << "\nMin sum:  " << sum << "\n";
  if (manager->getSettings().saveOutput) {
    fileOut << "\nMin sum:  " << sum;
  }

  fileOut.close();
}
