#include <iostream>
#include <vector>
using namespace std;

struct Node
{
  Node(int32_t v) : value(v), left(nullptr), right(nullptr){}
  int32_t value;
  Node* left,*right;
};

struct BinaryTree
{

  BinaryTree(vector<int32_t>& list)
  {
    int32_t start = 0;
    Constructor(root, list, start);
  }

  ~BinaryTree()
  {
    Destructor(root);
  }

  void Constructor(Node *&root, vector<int32_t>& data, int& index)
  {
    if(index >= data.size())
    {
      return;
    }
    int32_t e = data[index++];
    if(e == '#')
    {
      root = nullptr;
    }
    else
    {
      root = new Node(e);
      Constructor(root->left, data, index);
      Constructor(root->right,data, index);
    }
  }

  void Destructor(Node* root)
  {
    if (root != nullptr)
    {
      Destructor(root->left);
      Destructor(root->right);
      delete root;
    }
  }

  void PreVisit(Node* root)
  {
    if (root != nullptr)
    {
      cout<<root->value<<"  ";
      PreVisit(root->left);
      PreVisit(root->right);
    }
  }

  Node* root;
};

int main()
{
  vector<int32_t> list = {1,2,4,'#','#','#',3,'#',6,'#','#'};
  BinaryTree tree(list);
  tree.PreVisit(tree.root);
  cout<<endl;
  return 0;
}
