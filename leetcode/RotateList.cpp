#include <iostream>
using namespace std;


struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
  ListNode* rotateRight(ListNode* head, int k)
  {
    ListNode* last = head;
    int n = 0;
    if (head == nullptr || k == 0)
    {
      return head;
    }
    while (last != nullptr && k > n++)
    {
      last = last->next;
    }
    if (last == nullptr && k >= n)
    {
      k = k % n;
      n = 0;
      last = head;
      while (last != nullptr && k > n++)
      {
        last = last->next;
      }
    }
    if (last == nullptr || k == 0)
    {
      return head;
    }

    ListNode* pre = head;
    while (last->next != nullptr)
    {
      pre = pre->next;
      last = last->next;
    }
    ListNode* new_head = pre->next;
    pre->next  = last->next;
    last->next = head;
    head = new_head;
    return head;
  }
};

void Print(ListNode* head = nullptr)
{
  while (head != nullptr)
  {
    cout << head->val << "\t";
    head = head->next;
  }
  cout << endl;
}

int main()
{
  Solution s;
  int k = 0;
  ListNode node1(1), node2(2), node3(3), node4(4), node5(5);
  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;
  ListNode* head = &node1;
  Print(head);

  k = 0;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 0);
  Print(head);

  k = 1;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 1);
  Print(head);

  k = 2;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 2);
  Print(head);

  k = 3;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 3);
  Print(head);

  k = 4;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 4);
  Print(head);

  k = 5;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 5);
  Print(head);

  k = 6;
  cout << "------" << k << "-------" << endl;
  head = s.rotateRight(head, 6);
  Print(head);

}
