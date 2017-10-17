#include <iostream>
using namespace std;

 struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (n <= 0 || head == NULL)
    {
      return head;
    }
    int count = 0;
    ListNode* p = head;
    while (count < n && p != NULL)
    {
      ++count;
      p = p->next;
    }
    if (p != NULL)
    {
      ListNode* q = head;
      while (p->next != NULL)
      {
        q = q->next;
        p = p->next;
      }
      ListNode* t = q->next;
      q->next = t->next;
      delete t;
    }
    else if (count == n)
    {
      ListNode* t = head;
      head = t->next;
      delete t;
    }
    return head;
  }
};

int main()
{
  ListNode* n0 = new ListNode(1);
  ListNode* n1 = new ListNode(2);
  n0->next = n1;
  ListNode* n2 = new ListNode(3);
  n1->next = n2;
  ListNode* n3 = new ListNode(4);
  n2->next = n3;
  ListNode* n4 = new ListNode(5);
  n3->next = n4;
  ListNode* n5 = new ListNode(6);
  n4->next = n5;
  ListNode* n6 = new ListNode(7);
  n5->next = n6;
  Solution s;
  ListNode* head = s.removeNthFromEnd(n0,7);
  //head = s.removeNthFromEnd(head,1);
  //head = s.removeNthFromEnd(head,5);
  while (head != NULL)
  {
    cout<<head->val<<"  ";
    ListNode* t = head;
    head = head->next;
    delete t;
  }
  return 0;
}
