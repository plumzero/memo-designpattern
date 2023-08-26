
#include "observer.h"

int main()
{
  Subject* subject = new ValueSubject();
  Observer* observer1 = new DigitObserver();
  Observer* observer2 = new GraphObserver();
  
  subject->attach(observer1);
  subject->attach(observer2);
  
  subject->execute();
  
  delete observer1;
  delete observer2;
  delete subject;
  
  return 0;
}