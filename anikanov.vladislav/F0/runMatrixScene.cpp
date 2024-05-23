#include "runMatrixScene.hpp"

#include <iostream>

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
    } while (command != "Y" && command != "N");
    }
    return;
  }
}

void anikanov::RunMatrixScene::help(bool need_description)
{
  std::ostream *out = &manager->getOutputStream();
  for (const auto &command: commands) {
    *out << command.first;
    if (need_description) {
      *out << " - " << command.second;
    }
    *out << "\n";
  }
  *out << "\n";
}

std::vector< std::string > anikanov::RunMatrixScene::getOnlyCommands() const
{
  std::vector< std::string > onlyCommands;
  for (const auto &command: commands) {
    onlyCommands.push_back(command.first);
  }
  return onlyCommands;
}

