
去餐厅吃饭时，想要一杯喝的，服务员问: 要什么牌子的，有百事的，可口的，或者白水? 又问要不要加冰? 放不放糖？等等。

像上面，喝的水就是被修饰对象，而什么牌子的，是否加冰，是否加糖就是针对于这杯水的修饰器。

[具体实现示例](realize.cpp)

Food 类是一个抽象基类，其中定义了对食物的描述获取以及价格获取的方法。Drinks 是 Food 的子类，它也作为被修饰对象。DecoratorWithBrand, DecoratorWithIce 和 DecoratorWithSugar 是修饰类，它们无法独立存在，只能作为被修饰对象的依附存在，所以需要传入一个被修饰对象作为聚合成员。

无论是被修饰对象类(Drinks)还是修饰器类(DecoratorWithBrand 等)，由于它们均继承自统一的基类，所以在处理完成之后，本质上仍然可以看作是核心对象(加过修饰之后的)。

装饰器 DecoratorWithBrand 除了传入被修饰对象之外，还传入了自己的行为(brand)，达到对品牌选择的目的。

通过上面的例子可以看出，装饰器模式具有以下特点:
- 被装饰对象和装饰器有着相同的基类型，即具有一致性
- 可以用一个或多个装饰器包装一个对象，装饰后仍然是那个对象(具有相同基类型)，只不过加了装饰
- 装饰器可以在被装饰对象的行为之前与/或之后，加上自己的行为，以达到特定的目的
- 装饰器模式的一个缺点是会导致程序中增加许多功能类似的很小的类
