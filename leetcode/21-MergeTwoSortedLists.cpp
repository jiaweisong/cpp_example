#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == NULL || l2 == NULL)
    {
      return l1 == NULL ? l2 : l1;
    }
    ListNode* head = NULL, *before = NULL, *p = NULL, *q = NULL;
    if (l1->val <= l2->val)
    {
      head = l1;
      before = l1;
      p = l1->next;
      q = l2;
    }
    else
    {
      head = l2;
      before = l2;
      p = l2->next;
      q = l1;
    }
    while (p != NULL && q != NULL)
    {
      if (p->val <= q->val)
      {
        before = p;
        p = p->next;
      }
      else
      {
        ListNode* t = q->next;
        q->next = p;
        before->next = q;
        before = q;
        q = t;
      }
    }//end while   

    if (q != NULL)
    {
      before->next = q;
    }
    return head;
  }
};

int main()
{
  ListNode* l0 = new ListNode(1);
  ListNode* l1 = new ListNode(2);
  l0->next = l1;
  ListNode* l2 = new ListNode(6);
  l1->next = l2;
  ListNode* l3 = new ListNode(8);
  l2->next = l3;
  ListNode* l4 = new ListNode(9);
  l3->next = l4;

  ListNode* r0 = new ListNode(3);
  ListNode* r1 = new ListNode(4);
  r0->next = r1;
  ListNode* r2 = new ListNode(5);
  r1->next = r2;
  ListNode* r3 = new ListNode(7);
  r2->next = r3;
  Solution s;
  ListNode* head = s.mergeTwoLists(l0,r0);
  while (head != NULL)
  {
    cout<<head->val<<"  ";
    ListNode* t = head;
    head = head->next;
    delete t;
  }
  return 0;
}
