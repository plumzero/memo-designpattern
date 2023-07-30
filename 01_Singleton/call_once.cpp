
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <memory>

template <class T>
class SingleTon {
public:
  template <class... Args>
  static T *getInstance(Args &&... args) {
    static std::once_flag _flag;
    std::call_once(_flag, [&]() { _inst.reset(new T(args...)); std::cout << "=== call once ===" << std::endl;  });
    return _inst.get();
  }

  static void Destroy() { _inst.reset(); }

private:
  ~SingleTon() = default;
  SingleTon() = default;
  SingleTon(const SingleTon &) = delete;
  SingleTon &operator=(const SingleTon &) = delete;

private:
  static std::shared_ptr<T> _inst;
};

template <class T>
std::shared_ptr<T> SingleTon<T>::_inst = nullptr;

class Test
{
public:
  void print()
  { 
    // std::cout << "hello world" << std::endl;
  }
};

int main()
{
  std::vector<std::thread> threads;
  
  int i = 0;
  for (i = 0; i < 10; i++) {
    threads.push_back(std::thread([]{
      int k = 0;
      for (k = 0; k < 1000000; k++) {
        SingleTon<Test>::getInstance()->print();
      }
    }));
  }
  
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
  
  std::cout << "===== test success =====" << std::endl;
  
  return 0;
}
