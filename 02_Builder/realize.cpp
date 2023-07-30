
#include <string>
#include <iostream>
#include <map>

/** 定义建造者界面方法，便于扩展 */
class Builder
{
public:
  virtual void who() = 0;
  virtual void when() = 0;
  virtual void where() = 0;
  virtual void what() = 0;
};

class Director final
{
public:
  Director(Builder* ber) : builder(ber){}
  void construct() {
    std::cout << "========== start layout ==========" << std::endl;
    builder->who();
    builder->when();
    builder->where();
    builder->what();
    std::cout << "=========== end layout ===========" << std::endl;
  }
private:
  Builder* builder;
};

/** 定义具体的建造者 */
class HorrorBuilder : public Builder
{
public:
  virtual void who() override { std::cout << "Sadako Yamamura" << std::endl; }
  virtual void when() override { std::cout << "midnight" << std::endl; }
  virtual void where() override { std::cout << "television" << std::endl; }
  virtual void what() override { std::cout << "Sadako Yamamura climbed out television at midnight" << std::endl; }
};

class HumorBuilder : public Builder
{
public:
  virtual void who() override { std::cout << "Jim Carrey" << std::endl; }
  virtual void when() override { std::cout << "morning" << std::endl; }
  virtual void where() override { std::cout << "building" << std::endl; }
  virtual void what() override { std::cout << "Jin Carrey became the God in one building this morning" << std::endl; }
};

int main()
{
  Builder* horror = new HorrorBuilder();
  Builder* humor =  new HumorBuilder();
  
  {
    Director director(horror);
    director.construct();
  }
  {
    Director director(humor);
    director.construct();
  }
  
  return 0;
}