
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
#include <thread>
#include <chrono>

class NumberGenerator;

/** 观察者基类 - 子类定义如何对对象进行观察 */
class Observer
{
public:
  virtual void update(NumberGenerator* generator) = 0;
};

/** 要观察的对象基类 */
class NumberGenerator
{
public:
  typedef int value_type;
  
public:
  std::list<Observer*> observers; 
public:
  void addObserver(Observer* observer)
  {
    observers.push_back(observer);
  }
  void deleteObserver(Observer* observer)
  {
    observers.remove(observer);
  }
  void notifyObservers()
  {
    for (auto & ele : observers) {
      ele->update(this);
    }
  }
  virtual int getNumber() = 0;
  virtual void execute() = 0;
};

class RandomNumberGenerator : public NumberGenerator
{
public:
  int random;
  int number;
public:
  virtual int getNumber() override
  {
    return number;
  }
  virtual void execute() override
  {
    // Real business: generate a random and notify to all observers
    srand(time(nullptr));
    int i;
    for (i = 0; i < 20; i++) {
      number = rand() % 50;
      notifyObservers();  
    }
  }
};

class DigitObserver : public Observer
{
public:
  virtual void update(NumberGenerator* generator) override
  {
    std::cout << "DigitObserver: " << generator->getNumber() << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
};

class GraphObserver : public Observer
{
public:
  virtual void update(NumberGenerator* generator) override
  {
    std::cout << "GraphObserver: ";
    int i, count = generator->getNumber();
    for (i = 0; i < count; i++) {
      std::cout << "*";
    }
    std::cout << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
};

int main()
{
  NumberGenerator* generator = new RandomNumberGenerator();
  Observer* observer1 = new DigitObserver();
  Observer* observer2 = new GraphObserver();
  
  generator->addObserver(observer1);
  generator->addObserver(observer2);
  
  generator->execute();
  
  delete observer1;
  delete observer2;
  delete generator;
  
  return 0;
}