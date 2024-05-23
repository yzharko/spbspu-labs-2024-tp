#include <iostream>

#include <memory>

#include "sceneManager.hpp"
#include "mainMenuScene.hpp"

using namespace anikanov;

int main() {
  auto sceneManager = std::make_shared<SceneManager>(std::cin, std::cout);
  sceneManager->addScene("MainMenu", std::make_unique<MainMenuScene>(sceneManager));

  sceneManager->switchToScene("MainMenu");

  while (sceneManager->isRunning()) {
    sceneManager->update();
  }

  return 0;
}
