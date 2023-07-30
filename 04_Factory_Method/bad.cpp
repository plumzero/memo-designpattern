

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

class Telephone
{
public:
    Telephone(std::string sno) : sno(sno) {}
    ~Telephone() {}
    void printSno() { std::cout << sno << std::endl; }
protected:
    std::string sno;
};

class TelephoneFactory
{
public:
    Telephone* create(std::string sno) {
        Telephone* phone = createTelephone(sno);
        registerTelephone(phone);
        return phone;
    }
protected:
    Telephone* createTelephone(std::string sno) {
        return new Telephone(sno);
    }
    void registerTelephone(Telephone* phone) {
        telephones.push_back(phone);
    }
    std::vector<Telephone*> telephones;
};

int main()
{
    TelephoneFactory* factory = new TelephoneFactory();
    Telephone* phone1 = factory->create(SerialNumber()());
    Telephone* phone2 = factory->create(SerialNumber()());
    Telephone* phone3 = factory->create(SerialNumber()());
    
    phone1->printSno();
    phone2->printSno();
    phone3->printSno();
    
    return 0;
}