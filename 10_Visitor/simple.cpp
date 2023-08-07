
#include <iostream>

class Patch
{
public:
  void visit() {
    std::cout << "this is a patch" << std::endl;
  }
};

class Major
{
public:
  void print() {
    std::cout << "I am Major" << std::endl;
  }
  void accept(Patch* v) { print(); v->visit(); }
};

class Minor
{
public:
  void print() {
    std::cout << "I am minor" << std::endl;
  }
  void accept(Patch* v) { print(); v->visit(); }
};


int main()
{
  Major major;
  major.accept(new Patch());

  Minor minor;
  minor.accept(new Patch());

  return 0;
}