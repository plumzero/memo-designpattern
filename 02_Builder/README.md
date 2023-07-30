
### 说明

建造者模式是对一类事物或功能抽象化，得到通用的功能接口，将其作为界面。

比如要对文件进行操作，要操作的文件类型可能有 csv、json、excel 等，但不管怎样，都需要打开文件、关闭文件、读文件、写文件这些动作。那么很明显地，就可以将这些动作定义为接口，而开发者只需要在对应的功能接口中"建造"相应的功能即可，而实现类再调用这个接口类即可。

那么实现类应该如何使用接口类呢？一般的做法是在构造实现类，接口类对象以入参形式传入。比如:

```c++
  class FileOperator {
  public:
    FileOperator(FILE* file) : _file(file) {}
    ...
  private:
    FILE* _file;
  };
```

就像拍电影一样，一个导演可以拍摄多种题材的电影，如恐怖片或幽默片。每种题材的电影其剧本结构大致是一样的(都包括人物，时间，地点，事件等)。可以将每种剧本看作是一个建造者，这样导演就可以根据不同的建造者拍摄出不同题材的电影。

建造者模式比较容易理解，不作详述。

### 具体实现

[示例](realize.cpp)


### 相关的设计模式

Template Method 模式
- 在 Builder 模式中，Director 角色控制 Builder 角色。
- 在 Template 模式中，父类控制子类。

Composite 模式
- 有些情况下， Builder 模式生成的实例构造了 Composite 模式。

Abstract Factory 模式
- Builder 模式和 Abstract Factory 模式都用于生成复杂的实例。

Facade 模式
- 在 Builder 模式中，Director 角色通过组合 Builder 角色中的复杂方法向外部提供可以简单生成实例的接口(API)(相当于示例程序中的 construct 方法)。
- Facade 模式中的 Facade 角色则是通过组合内部模块向外部提供可以简单调用的接口(API)。