
### 说明

在 Observer 模式中，当观察对象的状态发生变化时，会通知给观察者。 Observer 模式适用于根据对象进行相应处理的场景。

### 实现

为实现一致性，抽象(接口)化观察者 Observer 。为了被观察对象的可供扩展，抽象化被观察对象 NumberGenerator 。

被观察对象 NumberGenerator 发生变化时，其会(调用接口)通知(notify)给所有的观察者 Observer。所以被观察对象内部应该聚合所有的观察者(这里通过 std::list 保存)。

[示例程序](realize.cpp)

### 注意

被观察对象中可能有多个 Observer 角色，在上述示例程序中，先添加到 list 中的 Observer 会先执行观察。在设计具体的观察者(ConcreteObserver)角色时，需要注意这些观察者的观察方法(这里是 update)的调用顺序，不能因为观察方法的调用顺序发生改变而产生问题。

要注意观察者的行为对观察对象可能造成的影响(如改写观察对象)。

虽然名为观察者，但实际上观察者角色并非主动地去观察，而是被动地接受来自被观察对象角色的通知。因此，观察者模式也被称为 **Publish-Subscribe(发布-订阅)模式**。

### 相关的设计模式

Mediator 模式
- 在 Mediator 模式中，有时会使用 Observer 模式来实现 Mediator 角色与 Colleague 角色之间的通信。
- 就"发送变化通知"这一点而言， Mediator 模式与 Observer 模式是类似的。不过，两种模式中，通知的目的和视角不同。
- 在 Mediator 模式中，虽然也会发送通知，不过那不过是为了对 Colleague 角色进行仲裁而已。
- 而在 Observer 模式中，将 Subject 角色的状态变化通知给 Observer 角色的目的则主要是为了使被观察角色和观察者角色同步。
