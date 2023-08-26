
要实现的**功能相同，但接口不同时**，适配器模式可以作为新旧接口之间的桥梁作用。

适配器模式有两种:
- 对象适配器模式(使用复合的适配器)
- 类适配器模式(使用继承的适配器)

### 对象适配器模式

对象适配器模式可以用于对接口的适配。

STL 容器适配器是一种对象适配器模式的使用方式。以 std::queue 为例，它可以以 std::list 或 std::deque 作为基础容器，通过对它们的接口进行适配，实现并暴露其所需要的队列接口功能。

std::queue 的定义如下:
```c++
  template<class T>
  class queue {
    ...
  protected:
    std::deque<T> c;
  public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference front() { return c.front(); }
    reference back() { return c.back(); }

    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
  };
```
在实际开发中，程序员也可以根据自己的需要，通过基础容器封装一些合适的数据结构工具，比如单调队列、环形队列来使用。这也是对容器的一种适配。

### 类适配器模式

类适配器模式通过继承来实现，而且用作继承的父类一般是具体类，因为只有这样才能达成对功能的适配(抽象类不实现具体功能)。

[类适配器模式示例](class_adpater.cpp)
