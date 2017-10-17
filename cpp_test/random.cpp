#include <iostream>
#include <random>
using namespace std;

template<typename Type>
Type random(Type min, Type max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<Type> unif(min, max);
   return unif(gen);
}

int main()
{

  cout << random(0., 10000.0)<< endl;
   return 0;
}

