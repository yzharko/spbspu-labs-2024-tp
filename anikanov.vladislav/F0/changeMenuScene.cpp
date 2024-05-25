#include "changeMenuScene.hpp"

#include <iostream>

#include "settings.hpp"

void anikanov::ChangeMenuScene::onCreate()
{
}

void anikanov::ChangeMenuScene::update()
{
  auto manager = this->manager.lock();
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";
  *in >> command;

  if (!exist(commands, command)) {
    help();
  } else {
    if (command == "input") {
      manager->getSettings().inputMatrix = !manager->getSettings().inputMatrix;
      *out << "New " << manager->getSettings();
    } else  {
      manager->getSettings().outputMatrix = !manager->getSettings().outputMatrix;
      *out << "New " << manager->getSettings();
    }
  }
  manager->switchToScene("MainMenu", false);
}

void anikanov::ChangeMenuScene::onClose()
{
}

void anikanov::ChangeMenuScene::help()
{
  auto manager = this->manager.lock();
  std::ostream *out = &manager->getOutputStream();
  *out << "Unexpected using of command \"/change\".\n"
          "Command signature: /change {input/output}\n"
          "\n"
          "Example of right usage:\n"
          "/change input\n\n";
}
