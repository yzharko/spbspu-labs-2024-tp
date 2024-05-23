#ifndef CHANGEMENUSCENE_HPP
#define CHANGEMENUSCENE_HPP

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class ChangeMenuScene : public Scene {
  public:
    ChangeMenuScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void update() override;
    void help(bool need_description = false);
  private:
    std::vector< std::string > commands{
        "input",
        "output",
    };
  };
}

#endif
