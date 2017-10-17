#include <iostream>
using namespace std;

 struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    if (head == NULL)
    {
      return NULL;
    }
    ListNode* p = head;
    ListNode* q = NULL;
    if (p != NULL && p->next != NULL)
    {
      q = p->next;
      p->next = q->next;
      q->next = p;
      head = q;
    }
    ListNode* before_p = p;
    p = p->next;
    while (p != NULL && p->next != NULL)
    {
      q = p->next;
      p->next = q->next;
      q->next = p;
      before_p->next = q;

      before_p = p;
      p = p->next;
    }
   return head; 
  }
};

int main()
{
  ListNode* n0 = new ListNode(1);
  ListNode* n1 = new ListNode(2);
  ListNode* n2 = new ListNode(3);
  ListNode* n3 = new ListNode(4);
  ListNode* n4 = new ListNode(5);
  ListNode* n5 = new ListNode(6);
  ListNode* n6 = new ListNode(7);
  n0->next = n1;
  n1->next = n2;
  /*
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;
  n5->next = n6;
*/
  Solution s;
  ListNode* head = s.swapPairs(n0);
  while (head != NULL)
  {
    cout<<head->val<<"  ";
    ListNode* t = head;
    head = head->next;
    delete t;
  }
  return 0;
}

