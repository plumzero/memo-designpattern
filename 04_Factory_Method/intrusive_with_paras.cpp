
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
  void* ctx_;
public:
  MessageOneHandler(void* ctx) : ctx_(ctx) {}
  void Print() override { std::cout << (char*)ctx_ << "Message One Handler" << std::endl; }
};

class MessageTwoHandler : public MessageHandler
{
  void* ctx_;
public:
  MessageTwoHandler(void* ctx) : ctx_(ctx) {}
  void Print() override { std::cout << (char*)ctx_ << "Message Two Handler" << std::endl; }
};

class Factory
{
public:
  void Register(MessageType type) {
    switch (type) {
      case MessageType::MessageOne:
      {
        producers_.insert({type, [](void* ctx)-> MessageHandler*{ return new MessageOneHandler(ctx);}});
      }
      break;
      case MessageType::MessageTwo:
      {
        producers_.insert({type, [](void* ctx)-> MessageHandler*{ return new MessageTwoHandler(ctx);}});
      }
      break;
    }
  }

  MessageHandler* CreateObject(MessageType type, void* ctx) {
    if (producers_.find(type) != producers_.end()) {
      return producers_[type](ctx);
    }
    return nullptr;
  }
private:
  std::map<MessageType, std::function<MessageHandler*(void*)>> producers_;
};

int main()
{
  char context[] = "This is ";

  Factory factory;

  factory.Register(MessageType::MessageOne);
  factory.Register(MessageType::MessageTwo);

  MessageHandler* handler1 = factory.CreateObject(MessageType::MessageOne, context);
  std::cout << handler1 << ", ";
  handler1->Print();

  MessageHandler* handler2 = factory.CreateObject(MessageType::MessageOne, context);
  std::cout << handler2 << ", ";
  handler2->Print();

  MessageHandler* handler3 = factory.CreateObject(MessageType::MessageTwo, context);
  std::cout << handler3 << ", ";
  handler3->Print();

  return 0;
}