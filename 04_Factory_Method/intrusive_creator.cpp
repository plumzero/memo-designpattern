
#include <iostream>
#include <map>
#include <functional>

enum class MessageType : uint16_t
{
  MessageOne = 1,
  MessageTwo = 2
};

class MessageHandler
{
public:
  virtual void Print() = 0;
  virtual ~MessageHandler() noexcept = default;
};

class MessageOneHandler : public MessageHandler
{
public:
  MessageOneHandler() {}
  void Print() override { std::cout << "Message One Handler" << std::endl; }
};

class MessageTwoHandler : public MessageHandler
{
public:
  MessageTwoHandler() {}
  void Print() override { std::cout << "Message Two Handler" << std::endl; }
};

class Factory
{
public:
  virtual MessageHandler* CreateObject() = 0;
};

class MessageOneHandlerFactory : public Factory
{
public:
  MessageHandler* CreateObject() {
    return new MessageOneHandler();
  }
};

class MessageTwoHandlerFactory : public Factory
{
public:
  MessageHandler* CreateObject() {
    return new MessageTwoHandler();
  }
};

int main()
{
  MessageOneHandlerFactory factory_one;
  MessageTwoHandlerFactory factory_two;


  MessageHandler* handler1 = factory_one.CreateObject();
  std::cout << handler1 << ", ";
  handler1->Print();

  MessageHandler* handler2 = factory_one.CreateObject();
  std::cout << handler2 << ", ";
  handler2->Print();

  MessageHandler* handler3 = factory_two.CreateObject();
  std::cout << handler3 << ", ";
  handler3->Print();

  return 0;
}