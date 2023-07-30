
### 说明

将多个对象组成一条职责链，然后按照它们在职责链上的顺序一个一个地找出到底应该谁来负责处理。这种模式被称为责任链(Chain of Responsibility)模式。

当一个人被要求做什么事情时，如果他可以做就自己做，如果不能做就将"要求"转给另外一个人。下一个如果可以自己处理，就自己做；如果也不能自己处理，就再转给另外一个人...这就是责任链模式。


### realize 实现

责任链就像一个链表，其成员是由基类 Support 的子类构成，所以链表成员与成员之间具有一致性。可能正因如此，才能够传递问题。

基类指针捕获问题(Trouble)后，会按照预先设定的责任顺序将该问题进行传递，直到问题解决，或者全部问责完毕。

[示例程序](realize.cpp)

### 责任链的应用及注意

在视窗系统中，用户有时需要可以自由地在视窗中添加控件(按钮和文本输入框等)。这时，责任链模式就有了用武之地。

与"事先确定哪个对象负责什么样的处理，当接收到请求时，立即让相应的对象去处理请求"相比，使用责任链模式确实导致处理请求发生了(同步)延迟。这是一个需要权衡的问题，如果请求和处理者之间的关系是确定的，而且需要非常快的处理速度时(比如一些实时程序)，不使用责任链模式更好一些。

### 相关的设计模式

Composite 模式
- 处理角色(这里是 Support 类族)经常会使用 Composit 模式。

Command 模式
- 有时会使用 Command 模式向处理角色发送请求。