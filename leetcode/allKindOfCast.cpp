#include <iostream>
     using namespace std;
 
     class Base
     {
     public:
         int _base;
         virtual void printinfo()
         {
              cout << "_base\n" << endl;
         }
     };
 
     class Derived : public Base
     {
     public:
         int _derived;
         virtual void printinfo()
         {
              cout <<" _derived\n" << endl;
         }
     };
 
     int main(void)
     {
         Base b1;
         Derived d1;
         int aInt = 10;
         long aLong = 11;
         float aFloat = 11.11f;
         double aDouble = 12.12;
 
 
         Base* pb1 = dynamic_cast<Base*>(&d1);
         pb1->printinfo();
         Derived* pd1 = dynamic_cast<Derived*>(pb1);                 // 编译时有warning，运行时出错
         pd1->printinfo();
         return 0;
}
