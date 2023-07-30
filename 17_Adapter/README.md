
## 适配器模式(Adapter)
- 要实现的**功能相同，但接口不同时**，适配器模式可以作为新旧接口之间的桥梁作用。
- 适配器模式有两种:
    + 对象适配器模式(使用委托的适配器)；
    + 类适配器模式(使用继承的适配器)；
- 既然突出**功能性适配**，就要注意其使用场景。不要对一个纯对象类应用适配器模式，因
  为它们一般是作为一个对象。不过**可以对功能对象类或纯功能类应用适配器模式**。

## 从 bad 开始实现起
- 场景: 旧的打印机落伍了，新开发出来的打印机不仅具有旧打印原有的功能，还包括其他一些
  更先进的功能。如果不想在新打印机功能中重新再实现一遍旧打印机的功能，可以这样做:
  ```c++
    class OldPrinter
    {
    public:
        void printFunctionA() {
            std::cout << "old printer function A" << std::endl;
        }
        void printFunctionB() {
            std::cout << "old printer function B" << std::endl;
        }
    };

    class NewPrinter : OldPrinter
    {
    public:
        void printFunctionA() {
            OldPrinter::printFunctionA();
        }
        void printFunctionB() {
            OldPrinter::printFunctionB();
        }
        void printFunctionC() {
            std::cout << "new printer function C" << std::endl;
        }
    };
  ```
    + NewPrinter 继承 OldPrinter 原有的属性，同时可以在此基础上添加新的属性(这里未实现)；
    + NewPrinter 自定义与 OldPrinter 同名函数，在这些函数中添加 OldPrinter 功能；
- 使用示例如下:
  ```c++
    NewPrinter np;
    
    np.printFunctionA();
    np.printFunctionB();
    np.printFunctionC();
  ```
- 示例程序: bad.cpp
  
## 问题来了...
- 但是，如果又有一款更新功能的打印机问世，里面不仅包含 OldPrinter 和 NewPrinter 的全部功能，
  同时又加入了其他的功能，该怎么办呢？
- 又比如，原本有两款旧功能的打印机，二者功能有交集但同时又有差异。现在出现了一款新功能的打
  印机，将这两款旧打印机的功能整合了起来，又怎么办呢？
- 如果再以 NewPrinter 为父类继承之，很明显拖沓而不优雅。
- 可以将更新款的打印机功能定义为一个抽象类，之后再派生出一个打印功能对象类重写抽象类接口。

## good 实现，灵活地添加 - 对象适配器模式
- 实现如下:
  ```c++
    class OldPrinter1
    {
    public:
        OldPrinter1() {}
        void printFunctionA() {
            std::cout << "old printer function A" << std::endl;
        }
        void printFunctionB() {
            std::cout << "old printer function B" << std::endl;
        }
    };

    class OldPrinter2
    {
    public:
        OldPrinter2() {}
        void printFunctionB() {
            std::cout << "old printer function B" << std::endl;
        }
        void printFunctionC() {
            std::cout << "old printer function C" << std::endl;
        }
    };

    class Printable
    {
    public:
        virtual void printA() = 0;
        virtual void printB() = 0;
        virtual void printC() = 0;
        virtual void printD() = 0;
    };

    class NewPrinter : public Printable
    {
    public:
        void printA() {
            op1.printFunctionA();
        }
        void printB() {
            op1.printFunctionB();   // 也可以是 op2.printFunctionB
        }
        void printC() {
            op2.printFunctionC();
        }
        void printD() {
            std::cout << "new printer function D" << std::endl;
        }
    private:
        OldPrinter1 op1;
        OldPrinter2 op2;
    };
  ```
  打印机的所有功能都在 Printable 中声明，今后无论是整合旧打印机功能(如 OldPrinter3)，还
  是添加新的打印机功能(如 E 功能)，都声明到 Printable 中，之后 NewPrinter 重写此方法。
- 使用示例如下:
  ```c++
    NewPrinter np;
    
    np.printA();
    np.printB();
    np.printC();
    np.printD();
  ```
- 示例程序: good.cpp

## better 实现，让程序更优雅 - 类适配器模式
- 功能就功能，为什么 NewPrinter 还要添加两个私有成员呢？这让程序员有了额外的关注点，浪费精
  力。而且很突兀，毕竟 OldPrinter1 和 OldPrinter2 类都没有成员啊，到了 NewPrinter 这里突然
  冒出来两个成员算怎么回事？这让实现 OldPrinter1 和 OldPrinter2 的人怎么看？
- 既然这样，就全部继承吧:
  ```c++
    class NewPrinter : public Printable, OldPrinter1, OldPrinter2
    {
    public:
        void printA() {
            printFunctionA();
        }
        void printB() {
            OldPrinter1::printFunctionB();  /** 有歧义，可以指定域操作符 */
        }
        void printC() {
            printFunctionC();
        }
        void printD() {
            std::cout << "new printer function D" << std::endl;
        }
    };
  ```
- 使用示例同 good.cpp
- 示例程序: better.cpp

## 相关的设计模式
- Bridge 模式
    + Adapter 模式用于连接接口(API)不同的类，而 Bridge 模式而用于连接类的功能层次结构与实现
      层次结构。
- Decorator 模式
    + Adapter 模式用于填补不同接口(API)之间的缝隙，而 Decorator 模式则是在不改变接口(API)的
      前提下增加新功能。

## 总结
- 无论哪种适配模式，都包括三部分: 被适配对象，目标对象和中间适配接口类。上述示例中，被适配对
  象为 OldPrinter1、OldPrinter2，目标对象是 NewPrinter, 中间适配接口类是 Printable 。
- 目标对象类派生自两个类: 被适配对象类和抽象接口适配类。目标对象类可以继承被适配对象类的具体
  功能，同时可以通过这些功能重写抽象类中定义的方法，以达到适配目的。
