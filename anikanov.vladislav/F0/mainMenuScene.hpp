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
    void update() override;
    void help(bool need_description = false);
  private:
    std::string sceneName = "Главное меню";
    std::vector< std::pair< std::string, std::string >> commands{
        command{"/help", "помощь по командам"},
        command{"/info", "вывод текущих настроек ввода/вывода"},
        command{"/change", "смена типа ввода/вывода"},
        command{"/save", "сохранить последний вывод если он существует"},
        command{"/run", "запуск ввода графа и алгоритма Крускала"},
        command{"/exit", "завершить программу"},
    };
  };
}


#endif
