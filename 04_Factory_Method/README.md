

某地创办了一个工厂，该工厂准备开设一条流水线，用于生产电话机。生产出来的电话机当然要作为商品出售。为了防止盗版，可以为该工厂出产的每台电话机分配一个独一无二的序列号，工厂作为备案，这样就可以追踪自己的产品。

### 不好的实现

开始的实现如下:
```c++
  class Telephone
  {
  public:
    Telephone(std::string sno) : sno(sno) {}
    ~Telephone() {}
    void printSno() { std::cout << sno << std::endl; }
  protected:
    std::string sno;
  };

  class TelephoneFactory
  {
  public:
    Telephone* create(std::string sno) {
      Telephone* phone = createTelephone(sno);
      registerTelephone(phone);
      return phone;
    }
  protected:
    Telephone* createTelephone(std::string sno) {
      return new Telephone(sno);
    }
    void registerTelephone(Telephone* phone) {
      telephones.push_back(phone);
    }
    std::vector<Telephone*> telephones;
  };
```
使用示例如下:
```c++
  TelephoneFactory* factory = new TelephoneFactory();
  Telephone* phone1 = factory->create(SerialNumber()());
  Telephone* phone2 = factory->create(SerialNumber()());
  Telephone* phone3 = factory->create(SerialNumber()());
  
  phone1->printSno();
  phone2->printSno();
  phone3->printSno();
```

[示例程序](bad.cpp)

### 使用工厂模式

电话行业蓬勃发展，厂里也意识到这个行业的竞争也在加剧...于是决定新开设一条电视机生产线。具体怎么做呢？

如果再像上面分别创建一个 Television 和 TelevisionFactory, 显然不方便管理。而且电气设备都有一些共同的功能或属性，这样的话就需要为每种设备分别进行添加，太麻烦了。

为了方便对各类电气设备的管理，将各种工厂类抽象出来。为了方便各类电气设备功能属性的修改，将电气设备类抽象出来。

实现如下:
```c++
  class Product
  {
  public:
    Product(std::string sno) : sno(sno) {}
    ~Product(){}
    virtual void printSno() { std::cout << sno << std::endl; }
    virtual void electricFunction() = 0;
  protected:
    std::string sno;
  };

  class Telephone : public Product
  {
  public:
    Telephone(std::string sno) : Product(sno) {}
    ~Telephone() {}
    
    void electricFunction() { std::cout << "communication" << std::endl; }
  };

  class Television : public Product
  {
  public:
    Television(std::string sno) : Product(sno) {}
    ~Television() {}
    
    void electricFunction() { std::cout << "video play" << std::endl; }
  };

  class Factory
  {
  public:
    Product* create(std::string sno) {
      Product* p = createProduct(sno);
      registerProduct(p);
      return p;
    }
  protected:
    virtual Product* createProduct(std::string sno) = 0;
    virtual void registerProduct(Product* product) { products.push_back(product); }
  public:
    std::vector<Product*> products;
  };

  class TelephoneFactory : public Factory
  {
  protected:
    Product* createProduct(std::string sno) {
      return new Telephone(sno);
    }
  };

  class TelevisionFactory : public Factory
  {
  protected:
    Product* createProduct(std::string sno) {
      return new Television(sno);
    }
  };
```
使用示例如下:
```c++
  Factory* tpf = new TelephoneFactory();
  Product* phone1 = tpf->create(SerialNumber()());
  Product* phone2 = tpf->create(SerialNumber()());
  Product* phone3 = tpf->create(SerialNumber()());
  phone1->electricFunction();
  phone2->electricFunction();
  phone3->electricFunction();
  
  Factory* tvf = new TelevisionFactory();
  Product* tv1 = tvf->create(SerialNumber()());
  Product* tv2 = tvf->create(SerialNumber()());
  Product* tv3 = tvf->create(SerialNumber()());
  tv1->electricFunction();
  tv2->electricFunction();
  tv3->electricFunction();
```

[示例程序](good.cpp)

实际上，一个工厂应该是既能生产电话机，又能生产电视机，但上面的实现把二者分离了，创建了两个工厂。而这只是为了方便学习的一种做法。

### 更一般的做法

这个工厂应该可以生产多种产品，所以需要对程序进行一些修改，如下:
```c++
  // good 实现中去掉工厂继承类，同时 Factory 类定义为实例类。其他不变。
  class Factory
  {
  public:
    Product* create(int type, std::string sno) {
      Product* p = createProduct(type, sno);
      registerProduct(p);
      return p;
    }
  protected:
    Product* createProduct(int type, std::string sno) { 
      switch (type) {
        case 1:
          return new Telephone(sno);
        case 2:
          return new Television(sno);
        default:
          return nullptr;
      }
    }
    void registerProduct(Product* product) { if (! product) products.push_back(product); }
  public:
    std::vector<Product*> products;
  };
```

使用示例如下:
```c++
  Factory* factory = new Factory();
  Product* product1 = factory->create(1, SerialNumber()());
  Product* product2 = factory->create(2, SerialNumber()());
  Product* product3 = factory->create(1, SerialNumber()());
  product1->electricFunction();
  product2->electricFunction();
  product3->electricFunction();
```
通过传入一个类型 type 来决定该工厂应该生产哪种产品。

[示例程序](rational.cpp)

也可以将上面的 Factory 定义为单例，但本测试不再实现。
