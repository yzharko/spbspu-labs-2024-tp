#include <iostream>

#include <memory>

#include "settings.hpp"
#include "sceneManager.hpp"
#include "mainMenuScene.hpp"
#include "changeMenuScene.hpp"

using namespace anikanov;

int main()
{
  Settings settings;
  auto sceneManager = std::make_shared< SceneManager >(settings, std::cin, std::cout);
  sceneManager->addScene("MainMenu", std::make_unique< MainMenuScene >(sceneManager));
  sceneManager->addScene("ChangeMenu", std::make_unique< ChangeMenuScene >(sceneManager));

  sceneManager->switchToScene("MainMenu");

  while (sceneManager->isRunning()) {
    sceneManager->update();
  }

  return 0;
}
