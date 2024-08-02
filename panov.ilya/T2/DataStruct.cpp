#include "DataStruct.h"
#include <sstream>
#include <iomanip>

namespace Panov {

  std::istream& operator>>(std::istream& in, std::complex<double>& c) {
    char ch;
    double real = 0.0, imag = 0.0;
    in >> ch;
    if (ch != '#') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ch;
    if (ch != 'c') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ch;
    if (ch != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> real >> ch >> imag >> ch;
    if (ch != ')') {
      in.setstate(std::ios::failbit);
    }
    c = std::complex<double>(real, imag);
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const std::complex<double>& c) {
    out << "#c(" << std::fixed << std::setprecision(1) << c.real() << " " << c.imag() << ")";
    return out;
  }

  std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    std::getline(is, line);
    std::istringstream input(line);

    char ch;
    std::string key;

    input >> ch;
    if (ch != '(') {
      is.setstate(std::ios::failbit);
      return is;
    }

    bool key1Read = false, key2Read = false, key3Read = false;
    data.key1 = { 0.0, 0.0 };
    data.key2 = { 0, 0 };
    data.key3 = "";

    while (input >> ch) {
      if (ch == ':') {
        input >> key;
        if (key == "key1") {
          key1Read = true;
          std::cout << "Reading key1...\n";
          input >> data.key1;
          std::cout << "Key1: " << data.key1 << std::endl;
        }
        else if (key == "key2") {
          key2Read = true;
          std::cout << "Reading key2...\n";
          char innerCh;
          long long n;
          unsigned long long d;
          input >> innerCh;
          if (innerCh != '(') {
            is.setstate(std::ios::failbit);
            return is;
          }
          input >> key >> n >> innerCh >> key >> d >> innerCh;
          if (key != "N" || innerCh != ':') {
            is.setstate(std::ios::failbit);
            return is;
          }
          data.key2 = { n, d };
          std::cout << "Key2: N=" << data.key2.first << " D=" << data.key2.second << std::endl;
        }
        else if (key == "key3") {
          key3Read = true;
          std::cout << "Reading key3...\n";
          std::getline(input, data.key3, '"');
          std::getline(input, data.key3, '"');
          std::cout << "Key3: " << data.key3 << std::endl;
        }
      }
      else if (ch == ')') {
        break;
      }
    }

    if (!key1Read || !key2Read || !key3Read || input.fail()) {
      is.setstate(std::ios::failbit);
    }
    return is;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:";
    out << "key1 " << data.key1;
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}
