
#include <string>
#include <iostream>
#include <map>

/** 定义界面方法(这里也叫做原型)，便于扩展 */
class Product
{
public:
  virtual void use(std::string s) = 0;
  virtual Product* createClone() = 0; /** 其实现应该是对当前对象的一个深拷贝。 */
};

class Manager final
{
public:
  void registor(std::string n, Product* p) {
    showcase[n] = p;
  }
  
  Product* create(std::string n) {
    try {
      Product* p = showcase.at(n);
      return p->createClone();
    } catch (std::out_of_range&) {
      /** 根据原型模式的语义，即根据给定实现创建克隆。如果没有找到给定实例，
        * 则返回为空。这个与工厂模式或享元模式不同 */
      return nullptr;
    }
  }
private:
  std::map<std::string, Product*> showcase;
};

/** 定义具体原型，主要关注 createClone 方法的实现 */
class MessageBox : public Product
{
public:
  MessageBox(){}
  MessageBox(const MessageBox& mb) : type(mb.type) {
    /** 通常地(尤其是成员变量中包括指针成员时)，需要重新定义拷贝构造函数 */
  }
  virtual void use(std::string s) override { std::cout << "MessageBox: " << s << std::endl; }
  virtual Product* createClone() override {
    /** 正因为很可能需要重新定义派生类的拷贝构造函数，所以 createClone 是在派生类而不是在基类中实现 */
    return new MessageBox(*this);   /** 调用拷贝构造函数 */
  }
public:
  int type;
};

class UnderlinePen : public Product
{
public:
  UnderlinePen(){}
  UnderlinePen(const UnderlinePen& up) : type(up.type) { }
  virtual void use(std::string s) override { std::cout << "UnderlinePen: " << s << std::endl; }
  virtual Product* createClone() override {
    return new UnderlinePen(*this);
  }
public:
  int type;
};

int main()
{
  Manager mgr;
  /** [1] 注册实例 */
  MessageBox* mbox = new MessageBox();
  MessageBox* wbox = new MessageBox();
  UnderlinePen* upen = new UnderlinePen();
  mgr.registor("message box", mbox);
  mgr.registor("warning box", wbox);
  mgr.registor("underline pen", upen);
  /** [2] 克隆实例并使用 */
  Product* p1 = mgr.create("message box");
  p1->use("Hello World!");
  
  Product* p2 = mgr.create("warning box");
  p2->use("Hello World!");
  
  Product* p3 = mgr.create("underline pen");
  p3->use("Hello World!");
  
  return 0;
}