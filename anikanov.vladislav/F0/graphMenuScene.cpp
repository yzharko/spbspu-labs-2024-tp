#include "graphMenuScene.hpp"

#include <limits>
#include <numeric>
#include <iostream>
#include <sstream>

#include "myAlgorithms.hpp"

void anikanov::GraphMenuScene::onCreate()
{
  auto manager = this->manager.lock();
  std::ostream *out = &manager->getOutputStream();
  *out << sceneName << "\n";
  *out << "Enter the graph using this commands:" << "\n";
  help(true);
}

void anikanov::GraphMenuScene::update()
{
  auto manager = this->manager.lock();
  std::istream *in = &manager->getInputStream();
  std::ostream *out = &manager->getOutputStream();

  std::string command = "";

  *in >> command;
  auto onlyCommands = getOnlyCommands();
  if (exist(onlyCommands, command)) {
    if (command == "/back") {
      *out << "Are you sure? [Y/N]: ";
      do {
        *in >> command;
        if (command == "Y") {
          manager->switchToScene("MainMenu");
        } else if (command == "N") {
          return;
        } else {
          *out << "Unexpected answer.\nAre you sure? [Y/N]: ";
        }
      } while (command != "Y" && command != "N");
    } else if (command == "/add") {
      int a = 0;
      int b = 0;
      int c = 0;
      if (!(*in >> a >> b >> c)) {
        *out << "Invalid input.\n";
        *out << "correct: 1 2 10\n";
        in->clear();
        in->ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        return;
      }
      edges.push_back(std::vector< int >{a, b, c});
      return;
    } else if (command == "/list") {
      int i = 1;
      *out << "Graph edges:" << "\n";
      for (const auto &edge: edges) {
        *out << i++ << ". " << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
      }
      *out << "\n";
      return;
    } else if (command == "/pop") {
      std::string index = "";
      in->clear();
      std::getline(*in, index);
      if (!index.empty()) {
        index = index.substr(1, index.size() - 1);
      }
      if (index.empty()) {
        if (!edges.empty()) {
          edges.erase(edges.begin() + (edges.size() - 1));
        } else {
          *out << "Edges list is empty.\n";
        }
        return;
      }
      try {
        int i = std::stoi(index);
        edges.erase(edges.begin() + (i - 1));
      } catch (const std::exception &ex) {
        *out << "Invalid input\n";
      }
      return;
    } else if (command == "/end") {
      return manager->stopRunning();
    }
  }

  *out << "This command doesn't exist. There are existing commands:\n";
  help();

  return;
}

void anikanov::GraphMenuScene::onClose()
{
  auto manager = this->manager.lock();

  auto answer = runKruskalMST(edges, edges.size());

  int sum = std::accumulate(answer.begin(), answer.end(), 0, [](int sum, const std::vector< int > &edge) {
    return sum + edge[2];
  });
  printAns(answer, sum, manager);

  std::ostream *out = &manager->getOutputStream();
  if (!manager->isRunning()) {
    *out << "Goodbye!\n";
  }
}

void anikanov::GraphMenuScene::help(bool need_description)
{
  auto manager = this->manager.lock();
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

std::vector< std::string > anikanov::GraphMenuScene::getOnlyCommands() const
{
  std::vector< std::string > onlyCommands;
  for (const auto &command: commands) {
    onlyCommands.push_back(command.first);
  }
  return onlyCommands;
}

