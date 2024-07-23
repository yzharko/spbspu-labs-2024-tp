#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "DataStruct.h"

int main() {
  using namespace panov;

  std::vector<DataStruct> data;

  while (true) {
    std::cout << "Выберите действие:\n";
    std::cout << "1. Ввод и сортировка данных\n";
    std::cout << "2. Запуск тестов\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1: {
      std::cout << "Введите данные (оставьте пустую строку для завершения ввода):\n";
      std::string line;
      while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
          break;
        }
        std::istringstream input(line);
        DataStruct ds;
        if (input >> ds) {
          data.push_back(ds);
        }
        else {
          std::cerr << "Ошибка в формате данных: " << line << '\n';
        }
      }

      std::sort(data.begin(), data.end());

      std::cout << "Отсортированные данные:\n";
      for (const auto& item : data) {
        std::cout << item << '\n';
      }
      break;
    }
    case 2: {
      std::cout << "Запуск тестов:\n";
      {
        std::istringstream input("(:key1 #c(1.0 -1.0):key2 (:N -1:D 5:):key3 \"data\":)");
        DataStruct ds;
        if (input >> ds) {
          std::cout << "Тест 1: " << ds << '\n';
        }
      }
      {
        std::istringstream input("(:key2 (:N -1:D 5:):key3 \"with : inside\":key1 #c(2.0 -3.0):)");
        DataStruct ds;
        if (input >> ds) {
          std::cout << "Тест 2: " << ds << '\n';
        }
      }
      {
        std::istringstream input("(:key1 #c(1.0 -1.0):key2 (:N 3:D 2:):key3 \"data\"");
        DataStruct ds;
        if (input >> ds) {
          std::cout << "Тест 3 (ожидалась ошибка): " << ds << '\n';
        }
      }

      break;
    }
    case 0:
      std::cout << "Выход из программы.\n";
      return 0;
    default:
      std::cerr << "Некорректный выбор, попробуйте еще раз.\n";
      break;
    }
  }
}
