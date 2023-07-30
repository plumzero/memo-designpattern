
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <algorithm>

class SingleTon
{
  static SingleTon* instance;
public:
  SingleTon(){ std::cout << "Construct SingleTon" << std::endl; }
  ~SingleTon(){}
public:
  static SingleTon* getInstance()
  {
    if (nullptr == instance) {
      instance = new SingleTon();
    }
    return instance;
  }
};

SingleTon* SingleTon::instance = nullptr;

int main()
{
  std::vector<std::thread> threads;
  
  int i = 0;
  for (i = 0; i < 10; i++) {
    threads.push_back(std::thread([]{
      int k = 0;
      for (k = 0; k < 1000000; k++) {
        SingleTon::getInstance();
      }
    }));
  }
  
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
  
  std::cout << "===== test success =====" << std::endl;
  
  return 0;
}