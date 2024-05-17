#include "commands.hpp"

void mihalchenko::help(std::ostream &out)
{
  setlocale(LC_ALL, "ru");
  out << "Список команд:\n\
  1. help - вывод всех комманд(активно сейчас)\n\
  2. open < filename > - открытие файла словаря, если его нет, то создать и открыть\n\
  3. close < filename > - закрытие файла filename, если такого файла нет, то вывести сообщение об ошибке\n\
  4. save < filename > - сохранение изменений в файле filename\n\
  5. edit < filename > - редактирование файла filename\n\
  6. insert < filename > < word > < frequency > - вставка пары слово-частота в файл filename\n\
  7. remove < filename > < word / frequency > - удаление элемента(ов) из словаря по слову / частоте / слову и частоте\n\
  8. find < filename > < word / frequency > - вывод элементов по слову или с заданной частотой\n\
  9. print < filename > < sort:alph / sort:freq > < reverse:true/false > - вывод отсортированных элементов файла\n\
  10. view < partOfName > - вывод названий существующих словарей, дополнительный параметр - часть от названия\n\
  11. clear <filename > < start > < stop > - очистить весь словарь или в выбранном диапазоне\n\
  12. merge < filename1 > < filename2 > - обмен содержимого словарей, если возникает проблема - \
  программа выводит сообщение об ошибке\n\
  13. unique < filename1 > < filename2 > < newFileName > - сохраняет уникальные элементы из словарей в новом файле, \
  если какого-то из файлов нет или возникает любая другая проблема - также выводится сообщение об ошибке\n\
  14. count < filename > < name / frequency > - подсчет элементов с таким же именем или частотой\n\
  15. size < filename > - вывести размер словаря\n";
}
