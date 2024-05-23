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
  private:
    std::string sceneName = "Kruskal's Algorithm for Finding Minimum Spanning Tree";
    std::vector< std::vector< int > > matrix;
    std::vector< std::string > commands{
        std::string{"/rewrite"},
        std::string{"/end"},
        std::string{"/back"},
    };
  };
}


#endif
