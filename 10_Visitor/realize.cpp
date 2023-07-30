
#include "realize.h"

void ListVistor::visit(File* file)  {
  std::cout << currentdir << "/" << file->getName() << std::endl;
}
void ListVistor::visit(Directory* directory) {
  std::cout << currentdir << "/" << directory->getName() << std::endl;
  std::string savedir = currentdir;
  currentdir = currentdir + "/" + directory->getName();
  for (const auto& ele : directory->entries) {
    ele->accept(this);
  }
}

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
  rootdir->accept(new ListVistor());
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
  rootdir->accept(new ListVistor());

  return 0;
}