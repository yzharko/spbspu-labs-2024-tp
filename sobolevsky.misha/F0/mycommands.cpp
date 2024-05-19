#include "mycommands.hpp"
#include <string>
#include <limits>
#include <algorithm>
#include <functional>

using mypair = std::pair< std::string, std::multimap< size_t, std::string > >;

void sobolevsky::getCommands(std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::exception();
  }
  out << "1.commands - вывод списка доступных пользователю команд\n";
  out << "2.loadAndCreate < filename > - загрузка текста из файла и создание частотного словаря\n";
  out << "3.delete < name > - удаление частотного словаря\n";
  out << "4.allDicts - выводит имена всех словарей\n";
  out << "5.compareDicts < name1 > < name2 > - сравнение двух частотных словарей\n";
  out << "6.rename < oldName > < newName > - переименование словаря\n";
  out << "7.select < name > - выбор словаря для дальнейшей работы конкретно только с ним одним\n";
  out << "7.1.1.holyTrinity - выводит три самых часто встречаемых слова в словаре\n";
  out << "7.1.2.holyTrinity -amount - выводит три самых часто встречаемых слова в словаре\n";
  out << "7.2.1.printDict -(n/all) - вывод отсортированного списка определенного кол-ва слов без их частоты\n";
  out << "7.2.2.printDict -(n/all) -amount - вывод отсортированного списка определенного кол-ва слов c их частотой\n";
  out << "7.3.unigueWords - выводит список уникальных слов без повторений\n";
  out << "7.4.wordCount - выводит кол-во слов в тексте\n";
  out << "7.5.save < filename > - сохраняет в файл txt весь отсортированный частотный словарь\n";
}
