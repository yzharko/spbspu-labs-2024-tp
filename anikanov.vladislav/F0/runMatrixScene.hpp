#ifndef RUNMATRIXSCENE_HPP
#define RUNMATRIXSCENE_HPP

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class RunMatrixScene : public Scene {
  public:
    RunMatrixScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help(bool need_description = false);
    std::vector< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Kruskal's Algorithm for Finding Minimum Spanning Tree";
    std::vector< std::vector< int > > matrix;
    std::vector< command > commands{
        command{"/rewrite", "Rewrite the matrix"},
        command{"/end", "Finish entering the matrix"},
        command{"/back", "Enter the main menu"},
    };
  };
}

#endif
