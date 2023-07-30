
#include <iostream>
#include <string>
#include <vector>

struct SerialNumber
{
    std::string operator()() {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        srand48(((long)ts.tv_sec * 1000000000L) + ts.tv_nsec);
        
        long lval = lrand48();
        
        std::string bin(reinterpret_cast<const char*>(&lval), 4);

        std::string hex;
        for (const auto & ele : bin) {
            hex.append(1, "0123456789ABCDEF"[static_cast<int>((unsigned char)ele) / 16]);
            hex.append(1, "0123456789ABCDEF"[static_cast<int>((unsigned char)ele) % 16]);
        }
        
        return hex;
    }
};

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

int main()
{
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
    
    return 0;
}