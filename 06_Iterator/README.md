
迭代器模式有些绕。先从最坏的实现开始做起，循序渐进。

自始至终不变的元素类:
```c++
  class Book
  {
  public:
    Book(std::string n) : name(n) {}
    std::string getName() { return name; }
  private:
    std::string name;
  };
```

### 一般的实现

对于一个对象的集合，如果想要遍历该集合中的每个元素(可能的话还会做一些操作)，可以为该集合定义一个迭代器，如下:
```c++
  class BookShelf
  {
  public:
    Book& at(int index) {
      return books.at(index);
    }
    BookShelf& append(const Book& book) {
      books.push_back(book);
      return *this;
    }
    size_t size() {
      return books.size();
    }
 
  private:
    std::vector<Book> books;
  };

  class BookShelfIterator
  {
  public:
    BookShelfIterator(const BookShelf& bs) : bs(bs), index(0) {}
    bool hasNext() {
      if (index < bs.size()) {
        return true;
      } else {
        return false;
      }
    }
    Book& next() {
      return bs.at(index++);
    }
  private:
    BookShelf  bs;
    int        index;
  };
```

上述定义了两个类，分别是集合类 BookShelf 及其迭代器类 BookShelfIterator，后者为前者专属，除此之外，别无二用。使用方法如下:
```c++
  BookShelf bookShelf;
  bookShelf.append(Book("Around the World in 80 Days"));
  bookShelf.append(Book("Bible"));
  bookShelf.append(Book("Cinderella"));
  bookShelf.append(Book("Daddy-Long-Legs"));
  
  BookShelfIterator it = BookShelfIterator(bookShelf);
  
  while (it.hasNext()) {
    Book book = it.next();
    std::cout << book.getName() << std::endl;
  }
```
可以看到实现思路大致是:
- 集合类 BookShelf 是迭代器类 BookShelfIterator 的一个成员，将集合类赋值给迭代器成员后，迭代器就可以对该集合进行遍历。
- 迭代器类似于一个对象操作句柄，它占有主导地位。
[示例程序](bad.cpp)

### 尝试将迭代器抽象出来

试想，如果集合类 BookShelf 的实现不再使用 std::vector ，而改用 std::list 了， 原来实现的迭代器成员方法 next 用到了 std::vector 中的 at 函数，但 std::list 却没有这个函数。怎么办？这时就需要重写 BookShelfIterator, 比较麻烦。

再试想，如果有两个项目，或者一个项目里面有多个集合类的实现，有的要用 std::vector, 有的要用 std::list, 还有些要用其他的... 在原来的实现中，类与类之间的耦合性较强，导致对一个类的修改可能很多类都要变化，甚至变化很大。

自然而然地，我们会想到对 BookShelfIterator 抽象出来一层进行解耦。
```c++
  class Iterator
  {
  public:
    virtual bool hasNext() = 0;
    virtual Book& next() = 0;
  };

  class BookShelfIterator : public Iterator
  {
  public:
    BookShelfIterator(BookShelf bs) : bs(bs), index(0) {}
    bool hasNext();
    Book& next();
  private:
    BookShelf  bs;
    int        index;
  };
```

定义一个名字为 Iterator 的抽象类，BookShelfIterator 由其派生并重写 hasNext 和 next 方法。

在一般的实现中， BookShelfIterator 占有主导权(类似于一个句柄)，而集合类 BookShelf 处于被动地位，这显得有些喧宾夺主了。一般的理解应该是: BookShelf 应该能够根据自身的实现(std::vector 或者 std::list 或者其它数据结构)有选择性的使用 BookShelfIterator(即如果现有迭代器不满足要求，可以另外写一个新的迭代器，而原来的迭代器可以不作任何修改)。怎么实现呢？

可以将迭代器抽象类 Iterator 定义为集合类的一个成员。或者可以再定义一个抽象类 Aggregate，里面封装一个返回迭代器抽象类 Iterator 的函数，之后集合类继承 Aggregate, 重写这个 iterator 函数。

第一种方法可能会涉及到对集体类构造函数的更改，相比之下更建议使用第二种，实现如下:
```c++
  class Aggregate
  {
  public:
    virtual Iterator* iterator() = 0;
  };

  class BookShelf : public Aggregate
  {
  public:
    Book& at(int index) {
      return books.at(index);
    }
    BookShelf& append(const Book& book) {
      books.push_back(book);
      return *this;
    }
    size_t size() {
      return books.size();
    }
    Iterator* iterator();
  private:
    std::vector<Book> books;
  };
```
为了实现多态， iterator 返回的是一个 Iterator 类型的指针。

类中函数实现如下:
```c++
  // BookShelfIterator 的 hasNext 和 next 成员函数相比 bad 实现并无太大变化
  bool BookShelfIterator::hasNext()
  {
    if (index < bs.size()) {
      return true;
    } else {
      return false;
    }
  }
  Book& BookShelfIterator::next() {
    return bs.at(index++);
  }
  Iterator* BookShelf::iterator() {
    return new BookShelfIterator(*this);
  }
```

BookShelf::iterator 的实现和下列语句很像，该语句也是 bad 实现中使用方法示例中的一条语句:
```c++
  BookShelfIterator it = BookShelfIterator(bookShelf);
```
不同的是，集合类 BookShelf 拥有对 BookShelfIterator 的主导权，它可以通过 iterator 去操作这个迭代器(句柄)。

如果集合类 BookShelf 的实现变化 std::list，通过重写 BookShelf::iterator 函数，就可以使用不同的迭代器，而这时仅需要修改一句代码。一句代码，无伤大雅。

使用方法示例如下:
```c++
  BookShelf bookShelf;
  bookShelf.append(Book("Around the World in 80 Days"));
  bookShelf.append(Book("Bible"));
  bookShelf.append(Book("Cinderella"));
  bookShelf.append(Book("Daddy-Long-Legs"));
      
  Iterator* it = bookShelf.iterator();
  
  while (it->hasNext()) {
    Book book = it->next();
    std::cout << book.getName() << std::endl;
  }
```
- [示例头文件](good.h)
- [示例实现文件](good.cpp)

### 让程序更优雅

在上面的抽象实现中，BookShelf::iterator 的实现用到了 new 操作符，每次调用都要 new 一个 BookShelfIterator 对象。但仔细想来 BookShelfIterator 只是一个方法类，一个进程中存在一个足矣。所以可以将其实现为单例类。

同时，因为 BookShelfIterator 依附于 BookShelf 而存在(即先有 BookShelf ，后有 BookShelfIterator )，所以在通过 BookShelf 创建 BookShelfIterator 时，只需要传递对前者的引用即可。
```c++
  class BookShelfIterator : public Iterator
  {
  public:
    static BookShelfIterator* getInstance(BookShelf& bs) {
      if (nullptr == instance) {
        instance = new BookShelfIterator(bs);
      }
      return instance;
    }
    static void destroyInstance() {
      if (instance) {
        delete instance;
      }
      instance = nullptr;
    }
  public:
    BookShelfIterator(BookShelf& bs) : bs(bs), index(0) {}
    bool hasNext();
    Book& next();
  private:
    static BookShelfIterator* instance;
    BookShelf&  bs;
    int        index;
  };

  BookShelfIterator* BookShelfIterator::instance = nullptr;
```

因为 BookShelfIterator 类的实例对象一直都在该进程中存在，所以 BookShelf::iterator 也可以修改为返回一个 Iterator 类型的引用。
```c++
  class Aggregate
  {
  public:
    virtual Iterator& iterator() = 0;
  };

  class BookShelf : public Aggregate
  {
  public:
    Book& at(int index) {
      return books.at(index);
    }
    BookShelf& append(const Book& book) {
      books.push_back(book);
      return *this;
    }
    size_t size() {
      return books.size();
    }
    Iterator& iterator();
  private:
    std::vector<Book> books;
  };
```

使用示例如下:
```c++
  BookShelf bookShelf;
  bookShelf.append(Book("Around the World in 80 Days"));
  bookShelf.append(Book("Bible"));
  bookShelf.append(Book("Cinderella"));
  bookShelf.append(Book("Daddy-Long-Legs"));
      
  Iterator& it = bookShelf.iterator();
  
  while (it.hasNext()) {
    Book book = it.next();
    std::cout << book.getName() << std::endl;
  }
```
可以看出，到这里迭代器使用方法与 Java 中的迭代器已大致相同。

### 相关的设计模式

Vistor 模式
- Iterator 模式是从集合中一个一个取出元素进行遍历，但是并没有在 Iterator 接口中声明对取出的元素进行何种处理
- Vistor 模式则是在遍历元素集合的过程中，对元素进行相同的处理
- 在遍历集合的过程中对元素进行固定的处理是常有的需求。Vistor 模式正是为了应对这种需求而出现的。在访问元素集合的过程中对元素进行相同的处理，这种模式就是 Vistor 模式。

Composite 模式
- Composite 模式是具有递归结构的模式，在其中使用 Iterator 模式比较困难。

Factory Method 模式
- 在 iterator 方法中生成 Iterator 的实例时可能会使用 Factory Method 模式。
    
### 总结

next 方法的语义是: 返回当前的元素，并指向下一个元素。之所以不用 ++，可能是因为像 std::list 这种数据结构，其元素并不是紧邻的，使用 next 更符合实际。

hasNext 方法的语义是: 确认接下来是否可以调用 next 方法。

迭代器的种类多种多样，在示例程序中展示的 Iterator 类只是很简单地从前向后遍历集合。其实遍历的方法是多种多样的:
- 从最后开始向前遍历
- 既可以从前向后遍历，也可以从后向前遍历(既有 next 方法也有 previous 方法)
- 指定下标进行"跳跃式"遍历
