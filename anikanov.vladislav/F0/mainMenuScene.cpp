#include "mainMenuScene.hpp"

#include <iostream>

void anikanov::MainMenuScene::update()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << ":\n";
  help();
}

void anikanov::MainMenuScene::help()
{
  std::ostream *out = &manager->getOutputStream();
  for (const auto &command: commands) {
    *out << command.first << " - " << command.second << "\n";
  }
  *out << "\n";
}
