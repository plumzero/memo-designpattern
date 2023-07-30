
#include <string>
#include <iostream>

/** 策略接口 - 抽象实现 */
class Strategy
{
public:
    virtual void startDo() = 0;
    virtual void justDo() = 0;
    virtual void endDo() = 0;
};

/** 具体实现策略 - 简单模式 */
class EasyStrategy : public Strategy
{
public:
    virtual void startDo() override { std::cout << "start easy" << std::endl; }
    virtual void justDo() override { std::cout << "execute easy" << std::endl; }
    virtual void endDo() override { std::cout << "end easy" << std::endl; }
};

/** 具体实现策略 - 中等模式 */
class MediumStrategy : public Strategy
{
public:
    virtual void startDo() override { std::cout << "start medium" << std::endl; }
    virtual void justDo() override { std::cout << "execute medium" << std::endl; }
    virtual void endDo() override { std::cout << "end medium" << std::endl; }
};

/** 具体实现策略 - 困难模式 */
class HardStrategy : public Strategy
{
public:
    virtual void startDo() override { std::cout << "start hard" << std::endl; }
    virtual void justDo() override { std::cout << "execute hard" << std::endl; }
    virtual void endDo() override { std::cout << "end hard" << std::endl; }
};

/** 无关辅助类 - 策略委托者 */
class Player
{
public:
    Player(const std::string& name, Strategy* strategy) {
        this->name = name;
        this->strategy = strategy;
    }
    void start() { strategy->startDo(); }
    void execute() { strategy->justDo(); }
    void end() { strategy->endDo(); }
    /** other method ... */
private:
    std::string name;
    Strategy* strategy;
};

int main()
{
    Player* player1 = new Player("Jim", new EasyStrategy());
    Player* player2 = new Player("Sam", new MediumStrategy());
    Player* player3 = new Player("Tom", new HardStrategy());
    
    player1->start();
    player2->execute();
    player3->end();
    
    return 0;
}