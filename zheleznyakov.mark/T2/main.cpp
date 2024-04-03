#include "structures.hpp"

int main()
{
  using zheleznyakov::Data;
  std::istringstream iss("(:key1 1.3d:key2 (:N -1:D 5:):key3 \"dat : a\":)");
  Data example;
  iss >> example;
  std::cout << example << "\n";
  return 0;
}
