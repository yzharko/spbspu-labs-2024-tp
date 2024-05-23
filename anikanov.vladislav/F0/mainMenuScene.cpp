#include "mainMenuScene.hpp"

#include <iostream>
#include <limits>

#include "inputHelper.hpp"

void anikanov::MainMenuScene::update()
{
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << ":\n";
  help(true);
  std::string command = "";
  while (command != "/exit") {
    if (readCommand(*in, command)) {
      *out << "Вы ввели: " << command << "\n";
    } else {
      in->clear();
      in->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      *out << "This command doesn't exist. There is a command list:\n";
      help();
    }
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
