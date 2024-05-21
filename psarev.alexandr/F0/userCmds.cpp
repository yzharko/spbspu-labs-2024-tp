#include "userCmds.hpp"
#include "internalFuncs.hpp"
#include <stdexcept>
#include <functional>

void psarev::cmdHelp(std::istream& in, std::ostream& out)
{
  if (in.get() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << "1. help - Displaying commands available to the user.\n";
  out << "2. create < filename > < name > - Creating a storage < name >, containing all the words from the text in the file < filename >, sorted by speechType.\n";
  out << "3. delete < name > - Deleting the < name > storage.\n";
  out << "4. list - Displaying the names of all existing storages.\n";
  out << "5. show < name > - Displaying all the speechType types and equivalent lists lengths in the < name > storage.\n";
  out << "6. rename < name > < newName > - Renaming < name > storage to < newName >.\n";
  out << "7. choose < name > - Selecting the < name > storage for further interaction with its elements.\n";
  out << "7.1 print < speechType > - Displaying a list of all words of the specified < speechType > from the choosed storage.\n";
  out << "7.2 fono < word > - Performing phonetic analisys of the word < word > and displaying the result on the screen.\n";
  out << "7.3 makeSent < num > - Making a sentence from numder <= < num > of each speech type in the choosed storage and displaying it on the screen.\n";
  out << "7.4 save < name > < dest > - Saving the < name > storage to the < dest > directory.\n";
}

void psarev::cmdCreate(std::map< std::string, storage_t >& depot, std::istream& in, std::ostream& out)
{
  std::string file = "";
  in >> file;
  if (!file.empty())
  {
    std::fstream fileIn;
    fileIn.open(file);
    if (fileIn.is_open())
    {
      std::string name = "";
      in >> name;
      if (!in)
      {
        std::cerr << "Error: Can't read the name!\n";
      }
      depot.emplace(name, storage_t());
      storage_t tempoStorage = depot[name];
      tempoStorage = readStorage(fileIn);
      out << "Storage " << name << " has been created!\n";
    }
  }
  else
  {
    std::cerr << "Error: File is empty!\n";
  }
}

void psarev::cmdChoose(std::map< std::string, storage_t >& depot, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (!in)
  {
    return;
  }

  std::map< std::string, std::function < void(storage_t&, std::istream&, std::ostream&) > > storageCmds;
  {
    using namespace std::placeholders;
    storageCmds["print"] = psarev::cmdPrint;
    storageCmds["fono"] = psarev::cmdFono;
    storageCmds["makeSent"] = psarev::cmdMakeSent;
  }

  std::string storageCmd = "";
  while (std::cin >> storageCmd)
  {
    try
    {
      storageCmds.at(storageCmd)(depot[name], std::cin, std::cout);
    }
    catch (const std::logic_error&)
    {
      psarev::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

void psarev::cmdDelete(std::istream& in, std::ostream& out, depot_t& depot)
{
  std::string tempoS = "";
  in >> tempoS;

  if (depot.erase(tempoS))
  {
    out << "Storage " << tempoS << " has been deleted!\n";
  }
  else
  {
    out << "Storage with name " << tempoS << "doesn't exists!\n";
  }
}
