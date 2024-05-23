#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <vector>
#include <memory>
#include <iosfwd>
#include "scene.hpp"
#include "settings.hpp"

namespace anikanov {

  class SceneManager : public std::enable_shared_from_this< SceneManager > {
  public:
    SceneManager(Settings &settings, std::istream &in, std::ostream &out);
    ~SceneManager() = default;

    void addScene(const std::string &name, std::unique_ptr< Scene > scene);
    void switchToScene(const std::string &name, bool needCreate = true);
    void update();
    void stopRunning();
    bool isRunning() const;

    std::istream &getInputStream();
    std::ostream &getOutputStream();
    void setOutputStream(std::ostream &out);
    Settings &getSettings();

  private:
    std::vector< std::pair< std::string, std::unique_ptr< Scene > > > scenes;
    std::unique_ptr< Scene > currentScene;
    bool running;
    std::istream &inputStream;
    std::ostream *outputStream;
    Settings &settings;
  };
}

#endif
