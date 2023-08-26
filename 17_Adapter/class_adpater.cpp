
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

class Operation : public JsonOperation, CsvOperation
{
public:
  void read_json() {
    JsonOperation::read();
  }
  void write_json() {
    write();
  }
  void read_csv() {
    CsvOperation::read();
  }
};

int main()
{
  Operation op;
  
  op.read_csv();
  op.read_json();
  op.write_json();
  
  return 0;
}