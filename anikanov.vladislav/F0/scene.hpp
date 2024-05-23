#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <string>

namespace anikanov {
  class SceneManager;

  class Scene {
  public:
    Scene(std::shared_ptr< SceneManager > manager) : manager(manager)
    {
    }
    virtual ~Scene() = default;
    virtual void update() = 0;

  protected:
    std::shared_ptr< SceneManager > manager;
  };
}

#endif
