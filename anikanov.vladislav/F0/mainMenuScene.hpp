#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <iostream>
#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  class MainMenuScene : public Scene {
  public:
    MainMenuScene(std::shared_ptr<SceneManager> manager) : Scene(manager) {}
    void update() override;
    void help();
  };
}


#endif
