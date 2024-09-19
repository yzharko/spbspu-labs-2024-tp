#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "sceneManager.hpp"

namespace anikanov {
  using command = std::pair< std::string, std::string >;

  class MainMenuScene : public Scene {
  public:
    MainMenuScene(std::shared_ptr< SceneManager > manager) : Scene(manager)
    {
    }
    void onCreate() override;
    void update() override;
    void onClose() override;
    void help(bool need_description = false);
    std::vector< std::string > getOnlyCommands() const;
  private:
    std::string sceneName = "Main menu";
    std::vector< std::pair< std::string, std::string >> commands{
        command{"/help", "command help"},
        command{"/info", "display current input/output settings"},
        command{"/change", "change input/output type"},
        command{"/save", "save last output if it exists"},
        command{"/run", "start graph input and Kruskal's algorithm"},
        command{"/exit", "exit program"},
    };
  };
}

#endif
