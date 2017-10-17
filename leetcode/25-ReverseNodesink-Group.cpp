#include <iostream>
using namespace std;

 struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == NULL || k < 2)
    {
      return head;
    }        
    int count = 1;
    ListNode* begin = head;
    ListNode* end = head;
    ListNode* last_end = NULL;
    bool first_time = true;

    while (begin != NULL)
    {
      end = begin;
      while (count < k && end != NULL)
      {
        ++count;
        end = end->next;
      }
      if (end != NULL)
      { 
        if (first_time == true)
        {
          head = end;
          first_time = false;
        }
        else
        {
          last_end->next = end;
        }
        
        last_end = begin;
        while (count > 1)
        {
           ListNode* t = begin->next;
           begin->next = end->next;
           end->next = begin;
           begin = t;
           --count;
        }
        begin = last_end->next;
      }
      else
      {
        begin = NULL;
        break;
      }
    }//end while (end != NULL) 
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
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;
  n5->next = n6;
  Solution s;
  ListNode* head = s.reverseKGroup(n0,4);
  while (head != NULL)
  {
    cout<<head->val<<"  ";
    ListNode* t = head;
    head = head->next;
    delete t;
  }
  return 0;
}
