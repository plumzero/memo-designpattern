
#include <string>
#include <iostream>

/** 类的实现层次结构 - 实现抽象层 */
class DisplayImpl
{
public:
    virtual void rawOpen() = 0;
    virtual void rawPrint() = 0;
    virtual void rawClose() = 0;
};

/** 类的实现层次结构 - 实现具体层 */
class StringDisplayImpl : public DisplayImpl
{
public:
    StringDisplayImpl(const std::string& s) {
        str = s;
        width = s.size();
    }
    virtual void rawOpen() override { printLine(); }
    virtual void rawPrint() override {
        std::cout << "|" + str + "|" << std::endl;
    }
    virtual void rawClose() override { printLine(); }
private:
    std::string str;
    int width;
    
    void printLine() {
        std::cout << "+";
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }
};

/** 类的功能层次结构 - 桥接到实现层 */
class Display /** not final */
{
public:
    Display(DisplayImpl* impl) {
        this->impl = impl;
    }
    void open() { impl->rawOpen(); }
    void print() { impl->rawPrint(); }
    void close() { impl->rawClose(); }
    void display() { open(); print(); close(); }
private:
    DisplayImpl* impl;
};
/** 类的功能层次结构 - 增加新功能 */
class CountDisplay : public Display
{
public:
    CountDisplay(DisplayImpl* impl) : Display(impl) {}
    
    void multiDisplay(int times) {
        open();
        for (int i = 0; i < times; i++) {
            print();
        }
        close();
    }
};

int main()
{
    Display* d1 = new Display(new StringDisplayImpl("Hello, China."));
    Display* d2 = new CountDisplay(new StringDisplayImpl("Hello, World."));
    CountDisplay* d3 = new CountDisplay(new StringDisplayImpl("Hello, Universe."));
    
    d1->display();
    d2->display();
    d3->display();
    
    d3->multiDisplay(5);
    
    return 0;
}