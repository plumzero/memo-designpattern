
#include <iostream>
#include <string>

class OldPrinter1
{
public:
    OldPrinter1() {}
    void printFunctionA() {
        std::cout << "old printer function A" << std::endl;
    }
    void printFunctionB() {
        std::cout << "old printer function B" << std::endl;
    }
};

class OldPrinter2
{
public:
    OldPrinter2() {}
    void printFunctionB() {
        std::cout << "old printer function B" << std::endl;
    }
    void printFunctionC() {
        std::cout << "old printer function C" << std::endl;
    }
};

class Printable
{
public:
    virtual void printA() = 0;
    virtual void printB() = 0;
    virtual void printC() = 0;
    virtual void printD() = 0;
};

class NewPrinter : public Printable, OldPrinter1, OldPrinter2
{
public:
    void printA() {
        printFunctionA();
    }
    void printB() {
        OldPrinter1::printFunctionB();  /** 有歧义，可以指定域操作符 */
    }
    void printC() {
        printFunctionC();
    }
    void printD() {
        std::cout << "new printer function D" << std::endl;
    }
};

int main()
{
    NewPrinter np;
    
    np.printA();
    np.printB();
    np.printC();
    np.printD();
    
    return 0;
}