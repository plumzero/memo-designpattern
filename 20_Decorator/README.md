
## 说明
- 简单应用场景举例:
  去餐厅吃饭时，想要一杯喝的，服务员问: 要什么牌子的，有百事的，可口的，或者白水? 又
  问要不要加冰? 放不放糖？等等。
- 像上面，喝的水就是被修饰对象，而什么牌子的，是否加冰，是否加糖就是针对于这杯水的修
  饰器。
  
## realize 实现
- Food 类是一个抽象基类，其中定义了对食物的描述获取以及价格获取的方法。Drinks 是 Food
  的子类，它也作为被修饰对象。DecoratorWithBrand, DecoratorWithIce 和 DecoratorWithSugar
  是修饰类，它们无法独立存在，只能作为被修饰对象的依附存在，所以需要传入一个被修饰对象
  作为聚合成员。
- 无论是被修饰对象类(Drinks)还是修饰器类(DecoratorWithBrand 等)，由于它们均继承自统一的
  基类，所以在处理完成之后，本质上仍然可以看作是核心对象(加过修饰之后的)。
- 装饰器 DecoratorWithBrand 除了传入被修饰对象之外，还传入了自己的行为(brand)，达到对品
  牌选择的目的。
- 较难理解，具体实现见: realize.cpp

## 装饰器模式特点说明
- 被装饰对象和装饰器有着相同的基类型，即具有一致性；
- 可以用一个或多个装饰器包装一个对象，装饰后仍然是那个对象(具有相同基类型)，只不过加了装饰；
- 装饰器可以在被装饰对象的行为之前与/或之后，加上自己的行为，以达到特定的目的；
- 装饰器模式的一个缺点是会导致程序中增加许多功能类似的很小的类。

## 继承和委托中的一致性
- 所谓一致性，简单来说就是:　可以将不同的东西当作当一种东西看待。
- 继承 - 父类和子类的一致性
    + 子类和父类具有一致性，对于如下两个类:
      ```c++
        class Parent {
            ...
            void parentMethod() { ... }
        };
        class Child : public Parent {
            ...
            void childMethod() { ... }
        };
      ```
    + 此时，Child 类的实例可以被保存在 Parent 类型的变量中，也可以调用从 Parent 类中继承
      的方法。
      ```c++
        Parent* obj = new Child();
        obj->parentMethod();
      ```
      也就是说，可以像操作 Parent 类的实例一样操作 Child 类的实例。这是将子类当作父类看待
      的一个例子。
    + 但是，反过来，如果想将父类当作子类一样操作，则需要先进行类型转换。
      ```c++
        Parent* obj = new Child();
        ((Child*)obj)->childMethod();
      ```
- 委托 - 自己和被委托对象的一致性
    + 使用委托让接口具有透明性(委托者和被委托对象具有完全一样的接口)时，自己和被委托对象具有
      一致性。
    + 对于下面的一个例子:
      ```c++
        class Violet {
            ...
            void method() { ... }
        };
        class Rose {
            ...
            Violet* obj;
            void method() { obj->method(); }
        };
      ```
      上面两个类虽然具有相同的 method 方法，且 Rose 将 method 方法委托给了 Violet，但除了方法
      名称以外，并没有其他的关联，也即 Violet 和 Rose 两个类不同，也不同当作同一种东西看待，不
      具有一致性。
    + 修改代码如下:
      ```c++
        class Flower { virtual void method() = 0; };
        class Rose : public Flower {
            Flower* obj; /** = Violet */
            void method() { obj->method(); }
        };
        class Violet : public Flower {
            void method() { ... }
        };
      ```
      这样就体现出了一致性，虽然 Rose 和 Violet 不相同，但可以当作同一种东西(Flower)看待。

## 相关的设计模式
- Adapter 模式
    + Decorator 模式可以在不改变被装饰物的接口(API)的前提下，为被装饰物添加装饰(透明性)。
    + Adapter 模式用于适配两个不同的接口(API)。
