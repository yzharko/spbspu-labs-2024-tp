#ifndef SCENE_HPP
#define SCENE_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "settings.hpp"

namespace anikanov {
  class SceneManager;

  class Scene {
  public:
    Scene(std::shared_ptr< SceneManager > &manager);
    virtual ~Scene() = default;
    virtual void onCreate() = 0;
    virtual void update() = 0;
    virtual void onClose() = 0;
    bool exist(std::vector< std::string > &list, std::string &command);

  protected:
    std::weak_ptr< SceneManager > manager;
    std::shared_ptr< Settings > settings;
  };
}

#endif
