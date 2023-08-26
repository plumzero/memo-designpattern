
原型模式是创建一个与给定实例完全相同的新的实现，不是对原来实例的引用或指向，本质上是对原来实例的**深拷贝**，这里称为克隆。

根据原型模式的语义，即根据给定实现创建克隆。如果没有找到给定实例，则返回为空。这个与工厂模式或享元模式不同。

在进行服务器开发时，会针对每种消息定义一个实现句柄函数。如果每个客户端连接需要维护各自的消息句柄函数状态，那么服务端侧就需要针对每个客户端保存一份各自的消息句柄函数对象。这个时候就可以使用原型模式为每个客户端连接"克隆"一份句柄函数。

这里首先定义一个句柄基类，如下:
```c++
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
```
在上面的实现中，clone() 为一个纯虚函数，它由子类实现，会返回指向具体子类对象的指针。addPrototype 会将消息类型及对应的消息句柄注册到一个映射表中。当需要创建一个某个消息类型的消息句柄对象时，可以通过调用 findAndClone() 来实现。而 handle 则是具体的消息处理函数。

这里将 addPrototype 和 findAndClone 定义为类的静态成员函数，以使抽象类可以直接使用这个方法。

[示例程序](handler.h)

如果使用者需要在创建时为对象传入参数，可以对 findAndClone 和 clone 稍加修改，并在每个子类中定义相应的构造函数即可。
