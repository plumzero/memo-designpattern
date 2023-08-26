
#include "handler.h"
#include <iostream>

class MessageHandlerOne : public MessageHandler
{
public:
  MessageHandlerOne() {}
  virtual MessageHandler* clone() override {
    return new MessageHandlerOne();
  }
public:
  virtual ~MessageHandlerOne() {}
  void handle() {
    std::cout << this << ": One" << std::endl;
  }
};

class MessageHandlerTwo : public MessageHandler
{
public:
  MessageHandlerTwo() {}
  virtual MessageHandler* clone() override {
    return new MessageHandlerTwo();
  }
public:
  virtual ~MessageHandlerTwo() {}
  void handle() {
    std::cout << this << ": Two" << std::endl;
  }
};

int main()
{
  MessageHandler::addPrototype(MessageOne, new MessageHandlerOne);
  MessageHandler::addPrototype(MessageTwo, new MessageHandlerTwo);

  MessageHandler* handler_one_1 = MessageHandler::findAndClone(MessageOne);
  MessageHandler* handler_one_2 = MessageHandler::findAndClone(MessageOne);
  MessageHandler* handler_two = MessageHandler::findAndClone(MessageTwo);

  handler_one_1->handle();
  handler_one_2->handle();
  handler_two->handle();

  return 0;
}