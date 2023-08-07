
#pragma once

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>

class NodeHandlerBase;
using NodeHandlerPtr = std::shared_ptr<NodeHandlerBase>;

class TopicsManager;
using TopicsManagerPtr = std::shared_ptr<TopicsManager>;

using Listener = std::function<void(const std::string&)>;
using ListenerMap = std::map<std::string, Listener>;

using StringSet = std::set<std::string>;

struct Config {
  std::string name = "";
};

class NodeHandlerWrapper {
 public:
  explicit NodeHandlerWrapper(const Config&);
  ~NodeHandlerWrapper();
  void Stop();
  bool Advertise(const StringSet&);
  bool Subscribe(const ListenerMap&);
  bool Subscribe(const std::string&, const Listener&);
  bool Publish(const std::string&, const std::string&);

 private:
  std::list<NodeHandlerPtr> node_handlers_;
  TopicsManagerPtr topics_manager_;
};
