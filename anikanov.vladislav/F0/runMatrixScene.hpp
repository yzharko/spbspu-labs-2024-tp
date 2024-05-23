#ifndef RUNMATRIXSCENE_HPP
#define RUNMATRIXSCENE_HPP

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  class RunMatrixScene : public Scene {
  public:
    RunMatrixScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void help(bool need_description = false);
  private:
    std::string sceneName = "Алгоритм Крускала для поиска минимального остовного дерева";
    std::vector< std::vector< int > > matrix;
    std::vector< std::string > commands{
        std::string{"/back"},
    };
  };
}


#endif
