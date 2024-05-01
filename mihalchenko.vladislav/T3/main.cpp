#include <iostream>
#include <fstream>
#include <limits>
// #include <map>
// #include <string>
// #include <vector>
// #include "functions.hpp"
#include "mapOfCommands.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Not enough input parameters...";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "The file cannot be opened\n";
    return 2;
  }
  using namespace mihalchenko;
  std::vector<Polygon> polygons;
  using del = DelimiterIO;
  while (!inputFile.eof())
  {
    std::copy(std::istream_iterator<Polygon>(inputFile),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));
    if (inputFile.fail())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  cmdWithStrings["AREA EVEN"] = printAreaEven;
  cmdWithStrings["AREA ODD"] = printAreaOdd;
  while (!std::cin.eof())
  {
    mihalchenko::Polygon polygon;
    std::string command = "";
    int n = 0;
    std::string firstPartOfCmd = "";
    std::string secondPartOfCmd = "";
    std::cin >> firstPartOfCmd;
    std::getline(std::cin, secondPartOfCmd);
    secondPartOfCmd.erase(0, 1);
    command = firstPartOfCmd + " " + secondPartOfCmd;
    // std::cout << command << "\n";
    bool isCmdWithTwoWords = false;
    try
    {
      if (cmdWithStrings.count(command))
      {
        doCmdWithStrings(command, polygons, std::cout << '\n');
        // std::cout << '\n';
      }
      if (cmdwithStringAndDigit.count(command))
      {
        n = std::stoi(secondPartOfCmd);
        doCmdWithStringAndDigit(command, polygons, n, std::cout << '\n');
        // std::cout << '\n';
      }
      if (cmdwithPolygon.count(command))
      {
        if (isCmdWithTwoWords)
        {
          std::cin >> polygon >> del{'\n'};
          if (!std::cin)
          {
            std::cout << "<INVALID COMMAND>";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }
        }
        else
        {
          // polygon = stringToPolygon(secondPartOfCmd);
        }
        doCmdWithDigitAndPolygon(command, polygons, polygon, std::cout);
        std::cout << '\n';
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
  }
}
