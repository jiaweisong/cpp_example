#include <iostream>
#include <stack>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
  public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    ListNode* head1 = l1;
	ListNode* head2 = l2;
	ListNode* head = NULL;
	int tmp = 0;
	
	if (head1 != NULL && head2 != NULL)
	{
	  int val = head1->val + head2->val;
	  if (val >= 10)
	  {
	    val = val % 10;
		tmp =1;
	  }
	  else 
	  {
		tmp = 0;
	  }
	  head = new ListNode(val);
	  head1 = head1->next;
	  head2 = head2->next;
	}
	else if (head1 != NULL)
	{
	  head = new ListNode(head1->val);
	  head1 = head1->next;
	}
	else if (head2 != NULL)
	{
	  head = new ListNode(head2->val);
      head2 = head2->next;	  
	}
	
	ListNode* current = head;
    while (head1 != NULL && head2 != NULL)
    {
      int val = head1->val + head2->val + tmp;
	  if (val >= 10)
	  {
	    val = val % 10;
		tmp =1;
	  }
	  else 
	  {
		tmp = 0;
	  }
	  ListNode* new_node = new ListNode(val);
	  current->next = new_node;
	  current = current->next;
      head1 = head1->next;
	  head2 = head2->next;
    }
	while (head1 != NULL)
    {
	  int val = head1->val + tmp;
	  if (val >= 10)
	  {
		val = val % 10;
		tmp = 1;
	  }
	  else 
	  {
		tmp = 0;
	  }
      ListNode* new_node = new ListNode(val);
	  current->next = new_node;
	  current = current->next;
      head1 = head1->next;
    }
    while (head2 != NULL)
    {
	  int val = head2->val + tmp;
	  if (val >= 10)
	  {
		val = val % 10;
		tmp = 1;
	  }
	  else 
	  {
		tmp = 0;
	  }
      ListNode* new_node = new ListNode(val);
	  current->next = new_node;
	  current = current->next;
      head2 = head2->next;
    }
	  
    if (tmp > 0)
	{
	  ListNode* new_node = new ListNode(tmp);
	  current->next = new_node;
	  current = current->next;
	}
	return head;
  }
};

int main()
{
  ListNode n1(1);
  ListNode n2(8);
  ListNode n3(0);
  n1.next = &n2;
  
  Solution s;
  ListNode* head = s.addTwoNumbers(&n1,&n3);
  while(head != NULL)
  {
	 cout<<head->val<<"    ";
	 head = head->next;
  }
  return 0;
}
