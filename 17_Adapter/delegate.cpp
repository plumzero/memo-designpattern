
#include <iostream>

class JsonOperation
{
public:
  JsonOperation() {}
  void read() {
    std::cout << "read json" << std::endl;
  }
  void write() {
    std::cout << "write json" << std::endl;
  }
};

class CsvOperation
{
public:
  CsvOperation() {}
  void read() {
    std::cout << "read csv" << std::endl;
  }
};

class Operation
{
public:
  void read_json() {
    jop.read();
  }
  void write_json() {
    jop.write();
  }
  void read_csv() {
    cop.read();
  }
private:
  JsonOperation jop;
  CsvOperation  cop;
};

int main()
{
  Operation op;
  
  op.read_csv();
  op.read_json();
  op.write_json();
  
  return 0;
}