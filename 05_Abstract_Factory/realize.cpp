
#include <string>
#include <iostream>

/** 界面抽象类 - 零件类 */
class Mechanical
{
public:
  virtual void setMechanical(std::string n) = 0;
  virtual std::string getMechanical() = 0;
};

class Electronic
{
public:
  virtual void setElectronic(std::string n) = 0;
  virtual std::string getElectronic() = 0;
};

class Electrical
{
public:
  virtual void setElectrical(std::string n) = 0;
  virtual std::string getElectrical() = 0;
};

/** 具体类 - 收音机 */
class RadioMechanical : public Mechanical
{
public:
  virtual void setMechanical(std::string n) override { name = n; }
  virtual std::string getMechanical() override { return name; }
private:
  std::string name;
};

class RadioElectronic : public Electronic
{
public:
  virtual void setElectronic(std::string n) override { name = n; }
  virtual std::string getElectronic() override { return name; }
private:
  std::string name;
};

class RadioElectrical : public Electrical
{
public:
  virtual void setElectrical(std::string n) override { name = n; }
  virtual std::string getElectrical() override { return name; }
private:
  std::string name;
};

/** 界面抽象类 - 工厂类 */
class Factory
{
public:
  virtual Mechanical* createMechanical() = 0;
  virtual Electronic* createElectronic() = 0;
  virtual Electrical* createElectrical() = 0; 
  virtual void ProductProduced() = 0;
};

/** 具体类 - 工厂类 */
class RadioFactory : public Factory
{
public:
  virtual Mechanical* createMechanical() override {
    ml = new RadioMechanical;
    return ml;
  }
  virtual Electronic* createElectronic() override {
    ec = new RadioElectronic;
    return ec;
  }
  virtual Electrical* createElectrical() override {
    el = new RadioElectrical;
    return el;
  }
  virtual void ProductProduced() {
    std::cout << ml->getMechanical() << std::endl;
    std::cout << ec->getElectronic() << std::endl;
    std::cout << el->getElectrical() << std::endl;
  }
private:
  /** 可以再封装一个类将这些成员包装进去。 */
  Mechanical* ml;
  Electronic* ec;
  Electrical* el;
};

int main()
{
  Factory* factory = new RadioFactory;
  Mechanical* ml = factory->createMechanical();
  Electronic* ec = factory->createElectronic();
  Electrical* el = factory->createElectrical();
  
  ml->setMechanical("Radio Mechanical");
  ec->setElectronic("Radio Electronic");
  el->setElectrical("Radio Electrical");
  
  factory->ProductProduced();
  
  return 0;
}