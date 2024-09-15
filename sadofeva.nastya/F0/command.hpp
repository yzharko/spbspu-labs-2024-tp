#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <iosfwd>
#include <map>
#include <string>

namespace sadofeva
{
	using dictionary = std::map<std::string, int>;
	void menuCommand(std::istream& in, std::ostream& out);
	void print(const std::map < std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
	void insert(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void remove(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void search(const std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void printMaxCountWorld(const std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void size(const std::map< std::string, dictionary>& dict, std::istream& in, std::ostream& out);
	void save(const std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void clear(std::map < std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void union1(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out);
	void countTo(const std::map < std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
}

#endif

