#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
using namespace std;

template<typename T>
T random(T min, T max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> unif(min, max);
   return unif(gen);
}

int random(int min, int max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> unif(min, max);
   return unif(gen);
}

#endif
