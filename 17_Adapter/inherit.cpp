
#include <iostream>

class JsonOperation
{
protected:
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
protected:
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