#include <iostream>
int main()
{
  int a = 0, b = 0;
  std::cin >> a >> b;
  if (std::cin.fail())
  {
    std::cerr << "error\n";
    return 1;
  }
  std::cout << a << " " << b << "\n";
  return 0;
}
