#include "Commands.hpp"
#include <regex>
#include <limits>
#include "ScopeGuard.hpp"

Commands::Commands(std::istream& in, std::ostream& out) :
  in_(in),
  out_(out),
  fin_{},
  dicts_()
{}

void Commands::help()
{
  out_ << "Available commands:\n";
  out_ << " help: display this help message\n";
  out_ << " openFile: open file with filename <filename>\n";
  out_ << " analyze: analyze the text from file\n";
  out_ << " closeFile: close the current file for reading\n";
  out_ << " print: output a table of words and lines in which they occur, to the console\n";
  out_ << " delete: delete an element from the dictionary\n";
  out_ << " exist: check the dictionary for the presence of an element with the key <key>\n";
  out_ << " search: output the numbers of lines with the given key in ascending order\n";
  out_ << " showSize: output the number of words in the dictionary\n";
  out_ << " remove: delete dictionary\n";
}

void Commands::openFile()
{
  if (fin_.is_open())
  {
    throw std::invalid_argument{ "Previous file is already open" };
  }
  out_ << "Enter the path to the file: ";
  std::string filename;
  in_ >> filename;
  std::ifstream fin(filename);
  if (!fin)
  {
    throw std::invalid_argument{ "Can't open file \"" + filename + "\"" };
  }
  fin_ = std::move(fin);
}

void Commands::analyze()
{
  if (!fin_ || !fin_.is_open())
  {
    throw std::logic_error{ "File not open" };
  }
  out_ << "Enter the dictname: ";
  std::string dictname;
  in_ >> dictname;

  WordsDict wdict;

  out_ << "Analyzing file...\n";
  auto word_regex = std::regex{ "\\w+" };
  std::string line;
  size_t i = 0;
  fin_.clear();
  fin_.seekg(0, fin_.beg);
  while (!fin_.eof())
  {
    std::getline(fin_, line);
    if (line.empty())
    {
      continue;
    }
    wdict.lines.emplace_back(line);

    auto words_begin = std::sregex_iterator{ line.begin(), line.end(), word_regex };
    auto words_end = std::sregex_iterator{};

    std::for_each(words_begin,
      words_end,
      [&wdict, i](auto it)
      {
        wdict.addWord(it.str(), i);
      });

    ++i;
  }

  dicts_[dictname] = wdict;

  out_ << "File have been analyzed!\n";
}

void Commands::closeFile()
{
  if (!fin_ || !fin_.is_open())
  {
    throw std::logic_error{ "Cannot close file. File not open" };
  }
  fin_.close();
}

void Commands::print()
{
  out_ << "Enter the dictname: ";
  std::string dictname;
  in_ >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  out_ << "Words Dictionary with name " << dictname << ": \n";
  out_ << dicts_.at(dictname);
}

void Commands::deleteKey()
{
  out_ << "Enter the key and dictname: ";
  std::string keyname, dictname;
  in_ >> keyname >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  auto& dict = dicts_.at(dictname).dict;

  if (dict.find(keyname) == dict.end())
  {
    throw std::logic_error{ "There is no key in dict with name \"" + dictname + "\"" };
  }

  dict.erase(keyname);

  out_ << "Key \"" << keyname << "\"was deleted\n";
}

void Commands::search() const
{
  out_ << "Enter the key and dictname: ";
  std::string keyname, dictname;
  in_ >> keyname >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  auto& dict = dicts_.at(dictname).dict;

  if (dict.find(keyname) == dict.end())
  {
    throw std::logic_error{ "There is no key in dict with name \"" + dictname + "\"" };
  }

  out_ << "This word on lines: ";
  for (auto&& l : dict.at(keyname))
  {
    out_ << l << ' ';
  }
  out_ << '\n';
}

void Commands::exist() const
{
  out_ << "Enter the key and dictname: ";
  std::string keyname, dictname;
  in_ >> keyname >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  auto& dict = dicts_.at(dictname).dict;

  out_ << (dict.find(keyname) == dict.end() ? "Key not exist" : "Key exist") << '\n';
}

void Commands::showSize() const
{
  out_ << "Enter dictname: ";
  std::string dictname;
  in_ >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  auto& dict = dicts_.at(dictname).dict;
  out_ << "In dict with name \"" << dictname << "\" " << dict.size() << " words\n";
}

void Commands::remove()
{
  out_ << "Enter dictname: ";
  std::string dictname;
  in_ >> dictname;

  if (dicts_.find(dictname) == dicts_.end())
  {
    throw std::logic_error{ "There is no dict with name \"" + dictname + "\"" };
  }

  dicts_.erase(dictname);

  out_ << "Dict with name \"" << dictname << "\" removed\n";
}

void Commands::invalidCommand()
{
  lisitsyna::iofmtguard guard(out_);
  if (in_.peek() == ' ')
  {
    in_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  out_ << "<INVALID COMMAND>\n";
}
