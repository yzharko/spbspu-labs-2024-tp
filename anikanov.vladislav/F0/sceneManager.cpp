#include "sceneManager.hpp"

anikanov::SceneManager::SceneManager() : currentScene(nullptr), running(true) {}

void anikanov::SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
  scenes.push_back({name, std::move(scene)});
}

void anikanov::SceneManager::switchToScene(const std::string& name) {
  for (auto& pair : scenes) {
    if (pair.first == name) {
      currentScene = std::move(pair.second);
      break;
    }
  }
}

void anikanov::SceneManager::update() {
  if (currentScene) {
    currentScene->update();
  } else {
    running = false;
  }
}

void anikanov::SceneManager::stopRunning() {
  running = false;
}

bool anikanov::SceneManager::isRunning() const {
  return running;
}
