#include "sceneManager.hpp"

#include <iostream>
#include <limits>

anikanov::SceneManager::SceneManager(Settings &setting, std::istream &in, std::ostream &out) : inputStream(in),
                                                                                               outputStream(&out),
                                                                                               settings(setting)
{
  this->currentScene = nullptr;
  this->running = true;
}

void anikanov::SceneManager::addScene(const std::string &name, std::unique_ptr< Scene > scene)
{
  scenes.push_back({name, std::move(scene)});
}

void anikanov::SceneManager::switchToScene(const std::string &name, bool needCreate)
{
  for (auto &pair: scenes) {
    if (pair.first == name) {
      currentScene = pair.second;
      break;
    }
  }
  if (needCreate) {
    currentScene->onCreate();
  }
}

void anikanov::SceneManager::update()
{
  if (currentScene) {
    currentScene->update();
  } else {
    running = false;
  }
}

void anikanov::SceneManager::stopRunning()
{
  running = false;
}

bool anikanov::SceneManager::isRunning() const
{
  return running;
}

std::istream &anikanov::SceneManager::getInputStream()
{
  return inputStream;
}

std::ostream &anikanov::SceneManager::getOutputStream()
{
  return *outputStream;
}

void anikanov::SceneManager::setOutputStream(std::ostream &out)
{
  outputStream = &out;
}

anikanov::Settings &anikanov::SceneManager::getSettings()
{
  return settings;
}
