#include <iostream>

using namespace std;

class base1
{
public:
  base1()
  {
    cout << "class base1" << endl;
  }
};
class base2
 {
 public:
   base2()
   {
     cout << "class base2" << endl;
   }
};

class level1: public base2, virtual public base1
{
public:
  level1()
  {
    cout << "class level 1" << endl;
  }
};

class level2: public base2, virtual public base1
{
public:
  level2()
  {
    cout << "class level 2" << endl;
  }
};

class toplevel: public level1, virtual public level2
{
public:
  toplevel()
  {
    cout << "class toplevel" << endl;
  }
};

int main()
{
  toplevel obj;
  return 0;
}
