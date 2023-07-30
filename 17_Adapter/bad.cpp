
#include <iostream>
#include <string>

class OldPrinter
{
public:
    void printFunctionA() {
        std::cout << "old printer function A" << std::endl;
    }
    void printFunctionB() {
        std::cout << "old printer function B" << std::endl;
    }
};

class NewPrinter : OldPrinter
{
public:
    void printFunctionA() {
        OldPrinter::printFunctionA();
    }
    void printFunctionB() {
        OldPrinter::printFunctionB();
    }
    void printFunctionC() {
        std::cout << "new printer function C" << std::endl;
    }
};

int main()
{
    NewPrinter np;
    
    np.printFunctionA();
    np.printFunctionB();
    np.printFunctionC();
    
    return 0;
}