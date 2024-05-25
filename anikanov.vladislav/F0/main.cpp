#include <iostream>

#include <memory>

#include "settings.hpp"
#include "sceneManager.hpp"
#include "mainMenuScene.hpp"
#include "changeMenuScene.hpp"
#include "runMatrixScene.hpp"

using namespace anikanov;

int main()
{
  Settings settings;
  auto sceneManager = std::make_shared< SceneManager >(settings, std::cin, std::cout);
  sceneManager->addScene("MainMenu", std::make_unique< MainMenuScene >(sceneManager));
  sceneManager->addScene("ChangeMenu", std::make_unique< ChangeMenuScene >(sceneManager));
  sceneManager->addScene("MatrixMenu", std::make_unique< RunMatrixScene >(sceneManager));

  sceneManager->switchToScene("MainMenu");

  while (sceneManager->isRunning()) {
    sceneManager->update();
  }

  return 0;
}

/*
0 7 8 0 0 0
7 0 11 2 0 0
8 11 0 6 9 0
0 2 6 0 11 9
0 0 9 11 0 10
0 0 0 9 10 0
*/
