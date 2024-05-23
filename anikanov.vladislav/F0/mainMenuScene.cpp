#include "mainMenuScene.hpp"

void anikanov::MainMenuScene::update()
{
  manager->getOutputStream() << "Main Menu\n";
  manager->stopRunning();
}

void anikanov::MainMenuScene::help()
{

}
