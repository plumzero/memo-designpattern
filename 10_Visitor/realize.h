
#include <string>
#include <iostream>
#include <vector>

class File;
class Directory;

class Visitor
{
public:
  virtual void visit(File* file) = 0;
  virtual void visit(Directory* directory) = 0;
};

class ListVistor : public Visitor
{
public:
  virtual void visit(File* file) override;
  virtual void visit(Directory* directory) override;
private:
  std::string currentdir;
};

class Entry
{
public:
  virtual std::string getName() = 0;
  virtual int getSize() = 0;
  virtual Entry* add(Entry* entry) { /** File 类不应该支持此方法 */
    throw std::runtime_error("not support file");
  }
  std::string toString() {
    return getName() + "(" + std::to_string(getSize()) + ")";
  }
  virtual void accept(Visitor* v) = 0;
};

class File : public Entry
{
public:
  File(const std::string& n, int s) : name(n), size(s) {}
  virtual std::string getName() override { return name; }
  virtual int getSize() override { return size; }
  virtual void accept(Visitor* v) override { v->visit(this); }
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
  virtual void accept(Visitor* v) override { v->visit(this); }

  std::vector<Entry*> entries;
private:
  std::string name;
};
