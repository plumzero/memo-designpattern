
#include <string>
#include <iostream>

/** 抽象类 - 食品类 */
class Food
{
public:
    virtual double getCost() = 0;
    virtual std::string getDescription() = 0;
};

/** 具体类 - 饮料类 */
class Drinks : public Food
{
public:
    virtual double getCost() override {
        return 1.0f;
    }
    virtual std::string getDescription() override {
        return "drinks";
    }
};
/** 饮料修饰类 */
class DecoratorWithBrand final : public Drinks
{
public:
    DecoratorWithBrand(Food* f, std::string b) : food(f), brand(b) {}
    virtual double getCost() override {
        if (brand == "Pepsi") { return food->getCost() + 2.5f; }
        else if (brand == "Coca Cola") { return food->getCost() + 2.8f; }
        else { return 0.0f; }
    }
    virtual std::string getDescription() override {
        return food->getDescription() + "," + brand;
    }
private:
    Food* food;
    std::string brand;
};
class DecoratorWithIce final : public Drinks
{
public:
    DecoratorWithIce(Food* f) : food(f) {}

    virtual double getCost() override {
        return food->getCost() + 0.8f;
    }
    virtual std::string getDescription() override {
        return food->getDescription() + ",Ice";
    }
private:
    Food* food;
};
class DecoratorWithSugar : public Drinks
{
public:
    DecoratorWithSugar(Food* f) : food(f) {}

    virtual double getCost() override {
        return food->getCost() + 0.5f;
    }
    virtual std::string getDescription() override {
        return food->getDescription() + ",Sugar";
    }
private:
    Food* food;
};
/** 也可以定义吃的东西，比如 肉类，再对肉类添加修饰，此处略 */
class Meats : public Food
{
public:
    virtual double getCost() override {
        
    }
    virtual std::string getDescription() override {
        
    }
};

int main()
{
    Food* drink = new DecoratorWithSugar(
                    new DecoratorWithIce(
                        new DecoratorWithBrand(
                            new Drinks(), "Coca Cola")));
    
    std::cout << drink->getDescription() << std::endl;
    std::cout << drink->getCost() << std::endl;
    
    return 0;
}