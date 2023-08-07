
class Store
{
public:
  virtual void open() = 0;
  virtual void serialize() = 0;
  virtual void close() = 0;
  void store() {
    open();
    serialize();
    close();
  }
};

class CsvStore : public Store
{

};

class JsonStore : public Store
{
  
};