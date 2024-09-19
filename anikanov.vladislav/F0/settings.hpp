#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iosfwd>

namespace anikanov {
  class Settings {
  public:
    Settings();
    bool inputMatrix;
    bool outputMatrix;
    bool saveOutput;
  };

  std::ostream &operator<<(std::ostream &out, const Settings &settings);
}

#endif
