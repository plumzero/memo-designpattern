
#include <iostream>
#include <string>
#include <type_traits>

class Feature
{
protected:
  Feature() {}
  virtual ~Feature(){}
public:
  virtual void* memory() = 0;
  
  template<typename T, typename... Args>
  void construct(Args&&... args) {
    void *mem = memory();
    new (mem) T(std::forward<Args>(args)...);
  }
};

template <typename T>
class Storage : public Feature
{
  typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
public:
  Storage() : Feature() {}
  virtual ~Storage() {}
public:
  virtual void* memory() override { return &object; }

  T& value() {
    return *reinterpret_cast<T*>(&object);
  }
};

class Apple
{
public:
  Apple(int i, std::string c) : index(i), color(c) {}
  ~Apple(){}
public:
  int index;
  std::string color;
};

int main()
{
  Storage<Apple> storeApple;
  storeApple.construct<Apple>(1, "red");
  
  storeApple.value().color = "Green";
  
  std::cout << "index=" << storeApple.value().index << std::endl;
  std::cout << "color=" << storeApple.value().color << std::endl; 

  return 0;
}
