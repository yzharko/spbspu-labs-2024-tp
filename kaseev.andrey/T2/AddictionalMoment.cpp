#include "AddictionalMoment.hpp"
#include <iostream>
void kaseev::ChangeD(std::string& str) {
  std::cout << "I ri=eached this point" << std::endl;
  bool flagQM = false;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '\"')
      flagQM = !flagQM;
    if ((str[i] == 'd' || str[i] == 'D') && !flagQM) {
      str.insert(i, 1, ' ');
      str[i+1] = 'd';
      return;
    }
  }
}
