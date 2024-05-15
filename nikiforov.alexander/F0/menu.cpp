#include "menu.hpp"
#include <iostream>

void nikiforov::printCommands()
{
  setlocale(LC_ALL, "Russian");

  std::cout << " 1. help - вывод списка доступных команд с параметрами\n";
  std::cout << " 2. create < filename > - создание частотного словаря из файла filename из папки с заданным названием\n";
  std::cout << " 3. open < mkdir > - чтение всех добавленных частотных словарей из папки mkdir\n";
  std::cout << " 4. delete < name > - удаление частотного словаря с названием name\n";
  std::cout << " 5. list - вывод названий всех существующих частотных словарей\n";
  std::cout << " 6. add < name1 > < name2 > - добавление частотного словаря name2 в словарь name1\n";
  std::cout << " 7. unite < newname > < name1 > < name2 > - создание словаря newname объединением двух словарей name1 и name2\n";
  std::cout << " 8. rename < name > < newname > - переименование словаря name на newname\n";
  std::cout << " 9. clear < name1 > < name2 > - удаление всех слов из словаря name1 которые есть в словаре name2\n";
  std::cout << " 10. save < mkdir > - сохранение словарей в папку mkdir в которую будут сохраняться словари в виде файлов\n";
  std::cout << " 11. select < name > - выбор словаря name, для которого будут производиться следующие команды\n";
  std::cout << " 12. print - вывод всего отсортированного списка слов с их частотой\n";
  std::cout << " 13. print < most > < n > - опция < most > c помощью параметра n выводит наиболее часто встречающиеся n слов\n";
  std::cout << " 14. print < count > - опция < count > позволяет вывести количество слов в словаре\n";
  std::cout << " 15. find < word > - найти и вывести информацию про слово с названием word\n";
  std::cout << " 16. erase < word > - удаление слова word\n";
}
