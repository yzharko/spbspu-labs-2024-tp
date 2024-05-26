#ifndef GRAPHMENUSCENE_HPP
#define GRAPHMENUSCENE_HPP

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class GraphMenuScene : public Scene {
  public:
    GraphMenuScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help(bool need_description = false);
    std::vector< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Kruskal's Algorithm for Finding Minimum Spanning Tree";
    std::vector< std::vector< int > > edges;
    std::vector< command > commands{
        command{"/add", "add edge"},
        command{"/list", "current entered list"},
        command{"/pop",
                "delete the i-th element in the list, if i is not specified, then the last element is deleted"},
        command{"/end", "Finish entering the matrix"},
        command{"/back", "Enter the main menu"},
    };
  };
}


#endif
