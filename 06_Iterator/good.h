
#ifndef __GOOD_H__
#define __GOOD_H__

#include <iostream>
#include <string>
#include <vector>

class Book
{
public:
  Book(std::string n) : name(n) {}
  std::string getName() { return name; }
private:
  std::string name;
};

class Iterator
{
public:
  virtual bool hasNext() = 0;
  virtual Book& next() = 0;
};

class Aggregate
{
public:
  virtual Iterator* iterator() = 0;
};

class BookShelf : public Aggregate
{
public:
  Book& at(int index) {
    return books.at(index);
  }
  BookShelf& append(const Book& book) {
    books.push_back(book);
    return *this;
  }
  size_t size() {
    return books.size();
  }
  Iterator* iterator();
private:
  std::vector<Book> books;
};

class BookShelfIterator : public Iterator
{
public:
  BookShelfIterator(BookShelf bs) : bs(bs), index(0) {}
  bool hasNext();
  Book& next();
private:
  BookShelf  bs;
  int        index;
};

#endif // ! __GOOD_H__