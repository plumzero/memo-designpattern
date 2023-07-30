
#include <iostream>
#include <vector>

class Book
{
public:
  Book(std::string n) : name(n) {}
  std::string getName() { return name; }
private:
  std::string name;
};

class BookShelf
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
  
private:
  std::vector<Book> books;
};

class BookShelfIterator
{
public:
  BookShelfIterator(const BookShelf& bs) : bs(bs), index(0) {}
  bool hasNext() {
    if (index < bs.size()) {
      return true;
    } else {
      return false;
    }
  }
  Book& next() {
    return bs.at(index++);
  }
private:
  BookShelf  bs;
  int        index;
};

int main()
{
  BookShelf bookShelf;
  bookShelf.append(Book("Around the World in 80 Days"));
  bookShelf.append(Book("Bible"));
  bookShelf.append(Book("Cinderella"));
  bookShelf.append(Book("Daddy-Long-Legs"));
  
  BookShelfIterator it = BookShelfIterator(bookShelf);
  
  while (it.hasNext()) {
    Book book = it.next();
    std::cout << book.getName() << std::endl;
  }
  
  return 0;
}