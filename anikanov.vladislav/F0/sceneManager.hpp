#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include "scene.hpp"

namespace anikanov {

  class SceneManager : public std::enable_shared_from_this< SceneManager > {
  public:
    SceneManager();
    ~SceneManager() = default;

    void addScene(const std::string &name, std::unique_ptr< Scene > scene);
    void switchToScene(const std::string &name);
    void update();
    void stopRunning();
    bool isRunning() const;

  private:
    std::vector< std::pair< std::string, std::unique_ptr< Scene>> > scenes;
    std::unique_ptr< Scene > currentScene;
    bool running;
  };
}

#endif
