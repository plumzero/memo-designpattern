
#include <string>
#include <iostream>
#include <vector>

/** 接口 - 抽象实现 */
class Entry
{
public:
    virtual std::string getName() = 0;
    virtual int getSize() = 0;
    virtual Entry* add(Entry* entry) { /** File 类不应该支持此方法 */
        throw std::runtime_error("not support file");
    }
    virtual void printList() { printList(""); }
    std::string toString() {
        return getName() + "(" + std::to_string(getSize()) + ")";
    }
    virtual void printList(const std::string& prefix) = 0;
};

/** 底层 - 具体实现 */
class File : public Entry
{
public:
    File(const std::string& n, int s) : name(n), size(s) {}
    virtual std::string getName() override { return name; }
    virtual int getSize() override { return size; }
    virtual void printList(const std::string& prefix) override {
        std::cout << prefix << "/" << name << std::endl;
    }
private:
    std::string name;
    int size;
};

class Directory : public Entry
{
public:
    Directory(const std::string& n) : name(n) {}
    virtual std::string getName() override { return name; }
    virtual int getSize() override {
        int size = 0;
        for (const auto& ele : entries) {
            size += ele->getSize();
        }
        return size;
    }
    virtual Entry* add(Entry* entry) override { entries.push_back(entry); return this; }
    virtual void printList(const std::string& prefix) override {
        std::cout << prefix << "/" << name << std::endl;
        for (const auto& ele : entries) {
            ele->printList(prefix + "/" + name);
        }
    }
    
private:
    std::string name;
    std::vector<Entry*> entries;
};

int main()
{
    std::cout << "Making root entries..." << std::endl;
    Entry* rootdir = new Directory("root");
    Entry* bindir = new Directory("bin");
    Entry* tmpdir = new Directory("tmp");
    Entry* usrdir = new Directory("usr");
    rootdir->add(bindir);
    rootdir->add(tmpdir);
    rootdir->add(usrdir);
    bindir->add(new File("vi", 10000));
    bindir->add(new File("latex", 20000));
    rootdir->printList();
    std::cout << std::endl;
    
    std::cout << "Making user entries..." << std::endl;
    Entry* yuki = new Directory("yuki");
    Entry* hanako = new Directory("hanako");
    Entry* tomura = new Directory("tomura");
    usrdir->add(yuki);
    usrdir->add(hanako);
    usrdir->add(tomura);
    yuki->add(new File("diary.html", 100));
    yuki->add(new File("Composite.java", 200));
    hanako->add(new File("memo.tex", 300));
    tomura->add(new File("game.doc", 400));
    tomura->add(new File("junk.mail", 500));
    rootdir->printList();
    
    return 0;
}