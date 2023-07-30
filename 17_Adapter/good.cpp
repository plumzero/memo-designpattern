
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

class NewPrinter : public Printable
{
public:
    void printA() {
        op1.printFunctionA();
    }
    void printB() {
        op1.printFunctionB();   /** 也可以是 op2.printFunctionB */
    }
    void printC() {
        op2.printFunctionC();
    }
    void printD() {
        std::cout << "new printer function D" << std::endl;
    }
private:
    OldPrinter1 op1;
    OldPrinter2 op2;
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