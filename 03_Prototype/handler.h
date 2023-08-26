
#pragma once

#include <map>

enum MessageType {
  MessageOne = 1,
  MessageTwo = 2
};

class MessageHandler
{
protected:
  virtual MessageHandler* clone() = 0;
public:
  static void addPrototype(MessageType type, MessageHandler* handler);
  static MessageHandler* findAndClone(MessageType type);
  virtual ~MessageHandler() noexcept = default;
  virtual void handle() = 0;

private:
  static std::map<MessageType, MessageHandler*> _map;
};

std::map<MessageType, MessageHandler*> MessageHandler::_map = {};

void MessageHandler::addPrototype(MessageType type, MessageHandler* handler)
{
  _map[type] = handler;
}

MessageHandler* MessageHandler::findAndClone(MessageType type)
{
  if (_map.find(type) != _map.end()) {
    return _map[type]->clone();
  }

  return nullptr;
}
