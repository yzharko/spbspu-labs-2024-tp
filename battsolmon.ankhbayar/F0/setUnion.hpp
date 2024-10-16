#ifndef SET_UNION_HPP
#define SET_UNION_HPP

#include <iostream>
#include <vector>

class setUnion {
public:
  setUnion(int size);

  int p(int v);
  void unite(int v1, int v2);
  int size() const;

  friend std::ostream& operator<<(std::ostream& out, setUnion& dsu);

private:
  std::vector<int> p_; // parent
  std::vector<int> r_; // rank
};

#endif
