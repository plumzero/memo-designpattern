
#include <iostream>
#include <map>
#include <functional>

enum class MessageType : uint16_t
{
  MessageOne = 1,
  MessageTwo = 2,
  MessageThr = 3
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

template<typename IdentifierType, class AbstractClass>
class Factory
{
public:
  template<IdentifierType id, class DerivedClass>
  void Register() {
    producers_.insert({id, []()-> AbstractClass*{ return new DerivedClass(); }});
  }

  AbstractClass* CreateObject(IdentifierType id) {
    if (producers_.find(id) != producers_.end()) {
      return producers_[id]();
    }
    return nullptr;
  }
private:
  std::map<IdentifierType, std::function<AbstractClass*()>> producers_;
};

int main()
{
  Factory<MessageType, MessageHandler> factory;

  factory.Register<MessageType::MessageOne, MessageOneHandler>();
  factory.Register<MessageType::MessageTwo, MessageTwoHandler>();
  
  MessageHandler* handler1 = factory.CreateObject(MessageType::MessageOne);
  std::cout << handler1 << ", ";
  handler1->Print();

  MessageHandler* handler2 = factory.CreateObject(MessageType::MessageOne);
  std::cout << handler2 << ", ";
  handler2->Print();

  MessageHandler* handler3 = factory.CreateObject(MessageType::MessageTwo);
  std::cout << handler3 << ", ";
  handler3->Print();

  return 0;
}