
在父类中定义处理流程的框架，在子类中实现具体处理的模式就称为 Template Method 模式。

这样，无论在父类类型的变量中保存哪个子类的实例，程序都可以正常工作，这种原则称为里氏替换原则。当然，该原则并非仅限于 Template Method 模式，它是通用的继承原则。

C++ 可以很容易地通过虚函数来实现这样的一种设计模式。

比如在定义一组报文时，报文在结构上由报头和载荷两部分组成。其中报头的格式是固定的，对于整个报文的解析方法也遵循一定流程。不同的是荷载数据结构以及对它们的解析细节。

实现者可以为这组报文定义一个公共基类，并在这个基类中定义并实现对每种报文的解析方法。同时声明一个抽象函数，这个抽象函数会由子类继续并实现它们各自对载荷类型的解析方式，这个抽象函数最终会由基类在它实现的解析方法中调用。
```c++
  class Message
  {
  private:
    uint8_t mProtocolVersion;
    const PayloadType mPayloadType;

  protected:
    static const std::size_t cHeaderSize{8};
    explicit Message(PayloadType payloadType) noexcept;
    Message(uint8_t protocolVersion, PayloadType payloadType) noexcept;
    virtual void GetPayload(std::vector<uint8_t> &payload) const = 0;
    virtual bool TrySetPayload(const std::vector<uint8_t> &payload,uint32_t payloadLength) = 0;

  public:
    void Serialize(std::vector<uint8_t> &serializedMessage) const
    {
      // 由基类实现
    }

    bool TryDeserialize(const std::vector<uint8_t> &serializedMessage, GenericNackType &nackCode)
    {
      // 由基类实现
    }

    virtual ~Message() noexcept = default;
  };
```
在上面对基类的实现中，暴露了两个接口 Serialize 和 TryDeserialize 分别用于对报文的序列化和反序列化处理。同时声明了两个纯虚函数 GetPayload 和 TrySetPayload，这两个纯虚函数由子类实现完成其各自对不同子类载荷部分的序列化和反序列化，并最终分别由基类在接口 Serialize 和 TryDeserialize 中调用。

[程序示例-基类实现](message.h)
[程序示例-子类实现](diag_message.h)

这里只对序列化函数进行了实现，反序列化函数类同。
