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
    void help(bool need_description = false);
    std::vector< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Алгоритм Крускала для поиска минимального остовного дерева";
    std::vector< std::vector< int > > matrix;
    std::vector< std::pair< std::string, std::string >> commands{
        command{"/rewrite", "написать новую матрицу"},
    };
  };
}


#endif
