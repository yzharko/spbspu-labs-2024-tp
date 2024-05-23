#include "runMatrixScene.hpp"

#include <iostream>
#include <sstream>

#include "settings.hpp"

void anikanov::RunMatrixScene::onCreate()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << "\n";
  *out << "Введите матрицу:" << "\n";
}

void anikanov::RunMatrixScene::update()
{
  if (matrix.size() != 0 && matrix.size() == matrix[0].size()) {
    std::ostream *out = &manager->getOutputStream();
    for (const auto &row: matrix) {
      for (const auto &elem: row) {
        *out << elem << " ";
      }
      *out << "\n";
    }
    manager->stopRunning();
  }
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";

  std::getline(*in, command);
  if (exist(commands, command)) {
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
  }

  std::vector<int> row;
  std::istringstream iss(command);
  std::string word;

  while (iss >> word) {
    try {
      row.push_back(std::stoi(word));
    } catch (const std::exception &e) {
      *out << "Неверный формат ввода.\n";
      return;
    }
  }

  if (row.size() != matrix.size() && matrix.size() != 0) {
    *out << "Неверное количество элементов в строке.\n";
    return;
  }
  matrix.push_back(row);

  return;
}
