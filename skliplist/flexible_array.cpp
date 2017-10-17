#include <iostream>
using namespace std;

struct Node
{
  int a;
  int *b;
};

int main()
{
  Node* ptr = (Node*)new char[sizeof(Node) + sizeof(5*sizeof(int))];
  ptr->b = (int*)ptr+1;
  int* bb = ptr->b;
  *bb = 100;
//  bb[0] = 100;
  return 0;
}
