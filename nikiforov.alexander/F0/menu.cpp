#include "menu.hpp"
#include <iostream>

void nikiforov::printCommands()
{
  std::cout << " 1. help - displaying a list of available commands with parameters\n";
  std::cout << " 2. create < filename > - creating a frequency dictionary from a filename file from a folder with a given name\n";
  std::cout << " 3. open < mkdir > - reading all added frequency dictionaries from the mkdir folder\n";
  std::cout << " 4. delete < name > - deleting a frequency dictionary with the name name\n";
  std::cout << " 5. list - output the names of all existing frequency dictionaries\n";
  std::cout << " 6. add < name1 > < name2 > - adding the name2 frequency dictionary to the name1 dictionary\n";
  std::cout << " 7. unite < newname > < name1 > < name2 > - creating a newname dictionary by combining two dictionaries name1 and name2\n";
  std::cout << " 8. rename < name > < newname > - renaming the dictionary name to newname\n";
  std::cout << " 9. clear < name1 > < name2 > - deleting all words from the name1 dictionary that are in the name2 dictionary\n";
  std::cout << " 10. save < mkdir > - saving dictionaries to the mkdir folder where dictionaries will be saved as files\n";
  std::cout << " 11. select < name > - selecting the name dictionary for which the following commands will be executed\n";
  std::cout << " 12. print - output of the entire sorted list of words with their frequency\n";
  std::cout << " 13. print < most > < n > - the < most > option uses the n parameter to output the most frequently occurring n words\n";
  std::cout << " 14. print < count > - the < count > option allows you to display the number of words in the dictionary\n";
  std::cout << " 15. find < word > - find and display information about a word with the name word\n";
  std::cout << " 16. erase < word > - deleting the word word\n";
}
