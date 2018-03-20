#include "std_memory_pool.h"

#define DEBUG
using namespace std;

struct Node
{
  int id;
  string name;
  char feature[1024];
};

int main()
{
  int* a = (int*)memory_pool::allocate(sizeof(int));
  *a = 1024;
  memory_pool::deallocate(a, sizeof(int));
  cout << a << endl;

  int* b = (int*)memory_pool::allocate(sizeof(int));
  *b = 100;
  cout << b << endl;

  int* c = (int*)memory_pool::allocate(sizeof(int));
  *c = 1;
  cout << c << endl;

  Node* node = (Node*) memory_pool::allocate(sizeof(Node));
  node->id = 10001;
  node->name = "songjw";

  cout << *a << endl;
  cout << node->id << "\t" << node->name << endl;
  return 0;
}
