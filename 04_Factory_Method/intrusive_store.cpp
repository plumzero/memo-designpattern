
#include <iostream>
#include <map>
#include <functional>
#include <vector>

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
  void Register(MessageType type) {
    switch (type) {
      case MessageType::MessageOne:
      {
        producers_.insert({type, []()-> MessageHandler*{ return new MessageOneHandler();}});
      }
      break;
      case MessageType::MessageTwo:
      {
        producers_.insert({type, []()-> MessageHandler*{ return new MessageTwoHandler();}});
      }
      break;
    }
  }

  MessageHandler* CreateObject(MessageType type) {
    if (producers_.find(type) != producers_.end()) {
      MessageHandler* handler = producers_[type]();
      objects_.push_back(handler);
      return handler;
    }
    return nullptr;
  }
private:
  std::map<MessageType, std::function<MessageHandler*()>> producers_;
  std::vector<MessageHandler*> objects_;
};

int main()
{
  Factory factory;

  factory.Register(MessageType::MessageOne);
  factory.Register(MessageType::MessageTwo);

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