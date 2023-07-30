
### 说明与注意

原型模式是创建一个与给定实例完全相同的新的实现，不是对原来实例的引用或指向，本质上是对原来实例的**深拷贝**，这里称为克隆。

根据原型模式的语义，即根据给定实现创建克隆。如果没有找到给定实例，则返回为空。这个与工厂模式或享元模式不同。

从实现来看，独立使用原型模式的情形应该很少，较常用于其他更复杂设计模式的子功能模式。

原型模式的思想: **在已有实例基础上克隆出完全相同的实例**。

### 具体实现

在多态继承体系下，常常可以看到原型模式的影子。如下:
```c++
  class Feature
  {
  protected:
    Feature() {}
    virtual ~Feature(){}
  public:
    virtual void* memory() = 0;
    
    template<typename T, typename... Args>
    void construct(Args&&... args) {
      void *mem = memory();
      new (mem) T(std::forward<Args>(args)...);
    }
  };

  template <typename T>
  class Storage : public Feature
  {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
  public:
    Storage() : Feature() {}
    virtual ~Storage() {}
  public:
    virtual void* memory() override { return &object; }

    T& value() {
      return *reinterpret_cast<T*>(&object);
    }
  };
  
  class Apple
  {
  public:
    Apple(int i, std::string c) : index(i), color(c) {}
    ~Apple(){}
  public:
    int index;
    std::string color;
  };
```
- Storage 继承自 Feature, 后者是个抽象类。可以将 Storage 看作是一个原型，Feature 是该原型的功能抽象接口类。
- 因为派生自 Feature 的子类，其构造方式相同，所以在抽象类中创建一个共同的定义方法 construct ，而该方法中调用的虚函数则在子类中具体实现。

- [示例程序](feature.cpp)
- [示例程序](realize.cpp)

其他注意事项见上述示例代码注释。

### 相关的设计模式

Flyweight 模式
- 使用 Prototype 模式可以生成一个与当前实例的状态完全相同的实例。
- 而使用 Flyweight 模式可以在不同的地方使用同一个实例。

Memento 模式
- 使用 Prototype 模式可以生成一个与当前实例的状态完全相同的实例。
- 而使 Memento 模式可以保存当前实例的状态，以实现快照和撤销功能。

Composite 模式以及 Decorator 模式
- 经常使用 Composite 模式和 Decorator 模式时，需要能够动态地创建复杂结构的实例。这时可以使用 Prototype 模式，以帮助我们方便地生成实例。

Command 模式
- 想要复制 Command 模式中出现的命令时，可以使用 Prototype 模式。
