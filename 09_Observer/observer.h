
#pragma once

#include <list>
#include <iostream>

class Subject;

class Observer
{
public:
  virtual void update(Subject* subject) = 0;
  virtual ~Observer() {}
};

// 被观察部分 - begin
class Subject
{  
public:
  std::list<Observer*> observers; 
public:
  void attach(Observer* observer)
  {
    observers.push_back(observer);
  }
  void remove(Observer* observer)
  {
    observers.remove(observer);
  }
  void notify()
  {
    for (auto & ele : observers) {
      ele->update(this);
    }
  }
  virtual void execute() = 0;
  virtual ~Subject() {}
};

class ValueSubject : public Subject
{
public:
  int count = 10;
public:
  virtual void execute() override
  {
    notify();
  }
};
// 被观察部分 - end

class DigitObserver : public Observer
{
public:
  virtual void update(Subject* subject) override
  {
    std::cout << static_cast<ValueSubject*>(subject)->count << std::endl;
  }
};

class GraphObserver : public Observer
{
public:
  virtual void update(Subject* subject) override
  {
    int count = static_cast<ValueSubject*>(subject)->count;
    for (int i = 0; i < count; i++) {
      std::cout << "*";
    }
    std::cout << std::endl;
  }
};

