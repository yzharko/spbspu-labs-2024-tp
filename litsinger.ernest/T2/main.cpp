#include <iostream>
#include <vector>
#include <bitset>


struct DataStruct{
  unsigned long long key1;
  unsigned long long key2;
  std::string key3;
};

struct colon_is_space : std::ctype<char> {
  colon_is_space() : std::ctype<char>(get_table()) {}
  static mask const* get_table()
  {
    static mask rc[table_size];
    rc[':'] = std::ctype_base::space;
    rc[' '] = std::ctype_base::space;
    rc['\n'] = std::ctype_base::space;
    return &rc[0];
  }
};

void swap(DataStruct &left, DataStruct &right);
bool chooseKey(std::string key, std::string value, DataStruct& myStruct);
int Partition(std::vector<DataStruct> &v, int start, int end);
void Quicksort(std::vector<DataStruct> &v, int start, int end );
void setStruct(std::vector<DataStruct>  &myVector);
void printVector(const std::vector<DataStruct>&  myVector);
bool isHex(std::string str);
bool isBinary(std::string str);

bool operator <(const DataStruct& left,const  DataStruct& right) {
  if (left.key1 < right.key1) {
    return true;
  }
  else if (left.key1 == right.key1) {
    if (left.key2 < right.key2) {
      return true;
    }
    else if (left.key2 == right.key2) {
      if (left.key3.size() < right.key3.size())
        return true;
    }
  }
    return false;
}
bool operator >(const DataStruct& left,const  DataStruct& right) {
  if (left.key1 > right.key1) {
    return true;
  }
  else if (left.key1 == right.key1) {
    if (left.key2 > right.key2) {
      return true;
    }
    else if (left.key2 == right.key2) {
      if (left.key3.size() > right.key3.size())
        return true;
    }
  }
    return false;
}
bool operator <=(const DataStruct& left,const  DataStruct& right) {
  if (left.key1 <= right.key1) {
    return true;
  }
  else if (left.key1 == right.key1) {
    if (left.key2 <= right.key2) {
      return true;
    }
    else if (left.key2 == right.key2) {
      if (left.key3.size() <= right.key3.size())
        return true;
    }
  }
  return false;
}
bool operator >=(const DataStruct& left,const  DataStruct& right) {
  if (left.key1 >= right.key1) {
    return true;
  }
  else if (left.key1 == right.key1) {
    if (left.key2 >= right.key2) {
      return true;
    }
    else if (left.key2 == right.key2) {
      if (left.key3.size() >= right.key3.size())
        return true;
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream& os,const DataStruct& myStruct){
  os << "(:key1 0b" << std::bitset<8> {myStruct.key1} << ":key2 0x" << std::hex << std::uppercase << myStruct.key2 <<
      ":key3 \"" << myStruct.key3 << "\":)";
  return os;
}
std::istream& operator>>(std::istream& is,DataStruct& myStruct) {
  std::string input;
  char hash;
  std::string key;
  std::string number;
  is >> hash;
  is.imbue(std::locale(is.getloc(), new colon_is_space));

  is >> key >> number;

  if ((number[0] != '0' and number[0] != '"' ) or ( number[1] != 'b' and number[1] != 'x' and number[number.size()-1] != '"')) {
    is >> key >> number >> key >> number >> hash;
    myStruct = {0,0,""};
    return is;
  }
  if (!chooseKey(key,number,myStruct)){
    is >> key >> number >> key >> number >> hash;
    myStruct = {0,0,""};
    return is;
  }
  is >> key >> number;
  if ((number[0] != '0' and number[0] != '"' ) or ( number[1] != 'b' and number[1] != 'x' and number[number.size()-1] != '"')) {
    is >> key >> number >> hash;
    myStruct = {0,0,""};
    return is;
  }
  if (!chooseKey(key,number,myStruct)){
    is >> key >> number >> hash;
    myStruct = {0,0,""};
    return is;
  }
  is >> key >> number;
  if ((number[0] != '0' and number[0] != '"' ) or ( number[1] != 'b' and number[1] != 'x' and number[number.size()-1] != '"')) {
    is >> hash;
    myStruct = {0,0,""};
    return is;
  }
  if(!chooseKey(key,number,myStruct)) {
    is >> hash;
    return is;
  }
  is >> hash;
  return is;
}


bool chooseKey(std::string key, std::string number, DataStruct& myStruct) {
  if (key == "key1") {
    number.erase(0, 2);
    if (isBinary(number)) {
      myStruct.key1 = stoll(number, 0, 2);
    }
    else {
      return false;
    }
  }
  else if (key == "key2") {
    number.erase(0, 2);
    if (isHex(number)) {
      myStruct.key2 = stoll(number, 0, 16);
    }
    else {
      return false;
    }
  }
  else if (key == "key3") {
    number.erase(0, 1);
    number.erase(number.size() - 1, 1);
    myStruct.key3 = number;
  }
  return true;
}


int Partition(std::vector<DataStruct> &v, int start, int end){
  int pivot = end;
  int j = start;
  for(int i=start;i<end;++i){
    if(v[i]<v[pivot]){
      swap(v[i],v[j]);
      ++j;
    }
  }
  swap(v[j],v[pivot]);
  return j;
}

void swap(DataStruct &left, DataStruct &right) {
  DataStruct tmp = left;
  left = right;
  right = tmp;
}

void Quicksort(std::vector<DataStruct> &v, int start, int end ){
  if(start<end){
    int p = Partition(v,start,end);
    Quicksort(v,start,p-1);
    Quicksort(v,p+1,end);
  }
}

void setStruct(std::vector<DataStruct>  &myVector){
  DataStruct dataStruct;
  while(true) {
    dataStruct = {0,0,""};
    std::cin >> dataStruct;
    if(std::cin.eof()){
      break;
    }
    if(dataStruct.key3.empty()){
      continue;
    }
    myVector.push_back(dataStruct);
  }
}


bool isBinary(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != '0' and str[i] != '1') {
      return false;
    }
  }
  return true;
}
bool isHex(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (!isdigit(str[i]) and !(str[i] >= 'a' and str[i] <= 'f') and !(str[i] >= 'A' and str[i] <= 'F')) {
      return false;
    }
  }
  return true;
}

void printVector(const std::vector<DataStruct>&  myVector){
  for(auto & i : myVector){
    std::cout << i << std::endl;
  }
}

int main() {
  std::vector<DataStruct>  myVector;
  etStruct(myVector);
  Quicksort(myVector, 0, myVector.size() -1);
  printVector(myVector);
  return 0;
}
