#include "runMatrixScene.hpp"

#include <iostream>
#include <sstream>

#include "myAlgorithms.hpp"

void anikanov::RunMatrixScene::onCreate()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << "\n";
  *out << "Enter the matrix:" << "\n";
}

void anikanov::RunMatrixScene::update()
{
  if (matrix.size() != 0 && matrix.size() == matrix[0].size()) {
    std::ostream *out = &manager->getOutputStream();
    if (!checkMatrix(matrix)) {
      *out << "The matrix is entered incorrectly. Enter again:\n";
      matrix.clear();
      return;
    }
    *out << "Entered matrix:\n";
    for (const auto &row: matrix) {
      for (const auto &elem: row) {
        *out << elem << " ";
      }
      *out << "\n";
    }
  }
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";

  std::getline(*in, command);
  if (exist(commands, command)) {
    if (command == "/back") {
      *out << "Are you sure? [Y/N]: ";
      do {
        *in >> command;
        if (command == "Y") {
          manager->switchToScene("MainMenu");
        } else if (command == "N") {
          return;
        } else {
          *out << "Unexpected answer.\nAre you sure? [Y/N]: ";
        }
      } while (command != "Y" && command != "N");
    } else if (command == "/rewrite") {
      *out << "Enter the matrix:" << "\n";
      return matrix.clear();
    } else if (command == "/end") {
      *out << "/end\n";
      return manager->stopRunning();
    }
  }

  if (command.empty()) {
    return;
  }

  std::vector< int > row;
  std::istringstream iss(command);
  std::string word;

  while (iss >> word) {
    try {
      row.push_back(std::stoi(word));
    } catch (const std::exception &e) {
      *out << "Invalid input format.\n";
      return;
    }
  }

  if (matrix.size() != 0 && row.size() != matrix[0].size()) {
    *out << "Incorrect number of elements in the line.\n";
    return;
  }

  if (row.size() == 0) {
    return;
  }
  matrix.push_back(row);

  return;
}
