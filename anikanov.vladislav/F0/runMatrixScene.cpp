#include "runMatrixScene.hpp"

#include <iostream>
#include <sstream>

#include "settings.hpp"

void anikanov::RunMatrixScene::onCreate()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << "\n";
  *out << "Введите матрицу:" << "\n";
  help(true);
}

void anikanov::RunMatrixScene::update()
{
  if (matrix.size() != 0 && matrix.size() == matrix[0].size()) {
    std::ostream *out = &manager->getOutputStream();
    *out << "Матрица квадратная.\n";
    manager->stopRunning();
  }
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";

  *in >> command;
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
    row.push_back(std::stoi(word));
  }

  matrix.push_back(row);

  return;
}
