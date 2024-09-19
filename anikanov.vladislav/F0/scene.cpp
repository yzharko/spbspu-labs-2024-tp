#include "scene.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

anikanov::Scene::Scene(std::shared_ptr< SceneManager > &manager)
{
  this->manager = manager;
}

bool anikanov::Scene::exist(std::vector< std::string > &list, std::string &command)
{
  return std::find(list.begin(), list.end(), command) != list.end();
}
