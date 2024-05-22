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
  out << "7.4 save < dest > - Saving whole depot to the < dest > directory.\n";
}

void psarev::cmdCreate(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot, std::string dest)
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
      tempoStorage = psarev::readStorage(fileIn);
      out << "Storage <" << name << "> has been created!\n";
    }
  }
  else
  {
    std::cerr << "Error: File is empty!\n";
  }
}

void psarev::cmdChoose(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot, std::string& storage)
{
  std::string chName = "";
  in >> chName;
  if (!in)
  {
    return;
  }

  auto chStorage = depot.find(chName);
  if (chStorage != depot.end())
  {
    storage = chName;
    out << "Storage <" << chName << "> has been choosen!\n";
  }
  else
  {
    out << "Dictionary <" << chName << "> doesn't exists!\n";
  }
}

void psarev::cmdDelete(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot)
{
  std::string tempoS = "";
  in >> tempoS;

  if (depot.erase(tempoS))
  {
    out << "Storage <" << tempoS << "> has been deleted!\n";
  }
  else
  {
    out << "Storage with name <" << tempoS << "> doesn't exists!\n";
  }
}

void psarev::cmdList(std::ostream& out, std::map< std::string, storage_t >& depot)
{
  for (auto iter = depot.begin(); iter != depot.end(); ++iter)
  {
    out << "Storage <" << (*iter).first <<"> \n";
  }
}

void psarev::cmdShow(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot)
{
  std::string tempoS = "";
  in >> tempoS;

  out << "Storage <" << tempoS << "> content:\n";

  for (auto iter = depot[tempoS].begin(); iter != depot[tempoS].end(); ++iter)
  {
    out << (*iter).first << ": " << ((*iter).second).size() << " ";
  }
}

void psarev::cmdRename(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot)
{
  std::string name = "";
  std::string newName = "";
  in >> name >> newName;

  auto desireSt = depot.find(name);
  if (desireSt != depot.end())
  {
    auto renamedSt = depot.find(newName);
    if (renamedSt == depot.end())
    {
      depot.emplace(newName, desireSt->second);
      depot.erase(desireSt);
      out << "Storage <" << name << "> has been renamed to <" << newName << ">!\n";
    }
    else
    {
      out << "Storage <" << newName << "> already exists! Try another name!" << "\n";
    }
  }
  else
  {
    out << "There is no storage <" << name << ">! Can't rename so!\n";
  }
}

void psarev::cmdSave(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot)
{
  std::string dest = "";
  in >> dest;
  std::string maekDest = "mkdir " + dest;

  std::ofstream fileOut;
  if (!std::system(maekDest.c_str()))
  {
    outDepot(dest, fileOut, depot);
    out << "Whole depot was printed at the directory <" << dest << ">!\n";
  }
  else
  {
    out << "Directory with that name already exists, do you want to overwrite it? (Y/N)\n";

    std::string decis = "";
    in >> decis;
    if (decis == "Y")
    {
      outDepot(dest, fileOut, depot);
      out << "Whole depot was printed at the directory <" << dest << ">!\n";
    }
    else if (decis == "N")
    {
      out << "Depot wasn't printed at the directory <" << dest << ">!\n";
    }
    else
    {
      out << "Please, type Y to print or N otherwise!" << "\n";
    }
  }
}

void psarev::cmdPrint(std::istream& in, std::ostream& out, std::map<std::string, storage_t>& depot, std::string& storage)
{
  std::string speechType = "";
  in >> speechType;
  if (!in)
  {
    return;
  }
  auto chStorage = depot.find(storage);
  storage_t curStorage = (*chStorage).second;
  for (auto iter = curStorage.begin(); iter != curStorage.end(); iter++)
  {
    if ((*iter).first == speechType)
    {
      out << (*iter).first << ": \n";
      for (size_t i = 0; i < (*iter).second.size(); i++)
      {
        out << (*iter).second[i] << " ";
      }
      out << "\n";
    }
  }
}
