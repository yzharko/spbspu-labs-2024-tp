#include "mainMenuScene.hpp"

#include <iostream>

#include "settings.hpp"

void anikanov::MainMenuScene::onCreate()
{
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << ":\n";
  help(true);
}

void anikanov::MainMenuScene::update()
{
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";
  std::vector< std::string > onlyCommands = getOnlyCommands();

  *in >> command;
  if (!exist(onlyCommands, command)) {
    *out << "This command doesn't exist. For a commands list type /help.\n";
    return;
  }
  if (command == "/help") {
    *out << "Command list:\n";
    help(true);
  } else if (command == "/info") {
    *out << manager->getSettings();
  } else if (command == "/change") {
    manager->switchToScene("ChangeMenu");
  } else if (command == "/save") {
    manager->getSettings().saveOutput = !manager->getSettings().saveOutput;
    *out << "New " << manager->getSettings();
  } else if (command == "/run") {
    manager->stopRunning();
  }
}

void anikanov::MainMenuScene::help(bool need_description)
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

std::vector< std::string > anikanov::MainMenuScene::getOnlyCommands() const
{
  std::vector< std::string > onlyCommands;
  for (const auto &command: commands) {
    onlyCommands.push_back(command.first);
  }
  return onlyCommands;
}
