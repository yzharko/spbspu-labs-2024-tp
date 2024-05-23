#include "mainMenuScene.hpp"

#include <iostream>

void anikanov::MainMenuScene::update()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << ":\n";
  help();
  manager->stopRunning();
}

void anikanov::MainMenuScene::help()
{
  std::ostream *out = &manager->getOutputStream();
  
}
