
#include "better.h"

bool BookShelfIterator::hasNext()
{
  if (index < bs.size()) {
    return true;
  } else {
    return false;
  }
}

Book& BookShelfIterator::next() {
  return bs.at(index++);
}

Iterator& BookShelf::iterator() {
  return *BookShelfIterator::getInstance(*this);
}

int main()
{
  BookShelf bookShelf;
  bookShelf.append(Book("Around the World in 80 Days"));
  bookShelf.append(Book("Bible"));
  bookShelf.append(Book("Cinderella"));
  bookShelf.append(Book("Daddy-Long-Legs"));
      
  Iterator& it = bookShelf.iterator();
  
  while (it.hasNext()) {
    Book book = it.next();
    std::cout << book.getName() << std::endl;
  }
  
  return 0;
}