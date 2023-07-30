
#include <string>
#include <iostream>

/** 辅助类 - 问题类 */
class Trouble
{
public:
  Trouble(int n) : number(n) {}
  int getNumber() { return number; }
  std::string toString() { return "[Trouble " + std::to_string(number) + "]"; }
private:
  int number;
};

/** 责任链 - 基类 */
class Support
{
public:
  Support(std::string n) : name(n) {}
  Support* setNext(Support* next) { /** 设置要推卸给的对象 */
    this->next = next;
    return next;
  }
  void support(Trouble trouble) {
    if (resolve(trouble)) {
      done(trouble);
    } else if (next != nullptr) {
      next->support(trouble);
    } else {
      fail(trouble);
    }
  }
  std::string toString() { return "[" + name + "]"; }
  virtual bool resolve(Trouble trouble) = 0;
  void done(Trouble trouble) {
    std::cout << trouble.toString() << " is resolved by " + toString() + "." << std::endl;
  }
  void fail(Trouble trouble) {
    std::cout << trouble.toString() << " cannot be resolved." << std::endl;
  }
  
private:
  std::string name;
  Support* next;
};

/** 责任链 - 子类 */
class NoSupport : public Support
{
public:
  NoSupport(std::string name) : Support(name) {}
  virtual bool resolve(Trouble trouble) override { return false; } /** 不作处理 */
};
class LimitSupport : public Support
{
public:
  LimitSupport(std::string name, int l) : Support(name), limit(l) {}
  virtual bool resolve(Trouble trouble) override {    /** 解决受限问题 */
    if (trouble.getNumber() < limit) {
      return true;
    } else {
      return false;
    }
  }
private:
  int limit;
};
class OddSupport : public Support
{
public:
  OddSupport(std::string name) : Support(name) {}
  virtual bool resolve(Trouble trouble) override {
    if (trouble.getNumber() % 2) {
      return true;
    } else {
      return false;
    }
  }
};

class SpecialSupport : public Support
{
public:
  SpecialSupport(std::string name, int n) : Support(name), number(n) {}
  virtual bool resolve(Trouble trouble) override {
    if (trouble.getNumber() == number) {
      return true;
    } else {
      return false;
    }
  }
private:
  int number;
};

int main()
{
    Support* alice   = new NoSupport("Alice");
    Support* bob     = new LimitSupport("Bob", 100);
    Support* charlie = new SpecialSupport("Charlie", 429);
    Support* diana   = new LimitSupport("Diana", 200);
    Support* elmo    = new OddSupport("Elmo");
    Support* fred    = new LimitSupport("Fred", 300);
    /** 设置责任链 */
    alice->setNext(bob)->setNext(charlie)->setNext(diana)->setNext(elmo)->setNext(fred);
    /** 制造各种问题 */
    for (int i = 0; i < 500; i += 33) {
      alice->support(Trouble(i));
    }
    
    return 0;
}