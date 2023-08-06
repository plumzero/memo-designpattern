
#include <iostream>
#include <map>
#include <functional>

#include "factory.h"

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

int main()
{
  char context[] = "This is ";
  
  // 1
  Factory<MessageType, MessageHandler, MessageHandler*(*)(void*)> factory;

  factory.Register(MessageType::MessageOne, [](void* ctx) -> MessageHandler* { return new MessageOneHandler(ctx); });
  factory.Register(MessageType::MessageTwo, [](void* ctx) -> MessageHandler* { return new MessageTwoHandler(ctx); });
  
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