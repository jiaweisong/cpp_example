#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  void Adjust(vector<ListNode*>& lists, int start)
  {
      int right = (start + 1) << 1;
      int size = lists.size();
      int minor = 0;
      ListNode* tmp = lists[start];
      while (right <= size)
      {
        if (right < size && lists[right]->val < lists[right - 1]->val)
        {
          minor = right;
        }
        else
        {
          minor = right - 1;
        }

        if (tmp->val > lists[minor]->val)
        {
          lists[start] = lists[minor];
          start = minor;
          right = (start + 1) << 1;
        }
        else
        {
          break;
        }
      }
      lists[start] = tmp;
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    for (int i = 0; i < lists.size();)
    {
      if (lists[i] == NULL)
      {
        lists[i] = lists.back();
        lists.pop_back();
      }
      else
      {
        ++i;
      }
    }
    if (lists.empty())
    {
      return NULL;
    }
    if (lists.size() == 1)
    {
      return lists[0];
    }

    for (int start = (lists.size() - 2) >> 1; start >= 0; --start)
    {
      Adjust(lists, start);
    }
    ListNode* head = lists[0];
    ListNode* tail = head;
    if (lists[0]->next == NULL)
    {
      lists[0] = lists.back();
      lists.pop_back();
    }
    else
    {
      lists[0] = lists[0]->next;
    }
    while (!lists.empty())
    {
      Adjust(lists, 0);

      ListNode *p = lists[0];
      tail->next = p;
      tail = p;

      if (lists[0]->next == NULL)
      {
        lists[0] = lists.back();
        lists.pop_back();
      }
      else
      {
        lists[0] = lists[0]->next;
      }
    }    
    return head;
  }
};

int main()
{
  ListNode* a0 = new ListNode(1);
  ListNode* a1 = new ListNode(4);
  ListNode* a2 = new ListNode(5);
  ListNode* a3 = new ListNode(9);
  a0->next = a1;
  a1->next = a2;
  a2->next = a3;

  ListNode* b0 = new ListNode(2);
  ListNode* b1 = new ListNode(3);
  ListNode* b2 = new ListNode(4);
  ListNode* b3 = new ListNode(7);
  b0->next = b1;
  b1->next = b2;
  b2->next = b3;


  ListNode* c0 = new ListNode(3);
  ListNode* c1 = new ListNode(6);
  ListNode* c2 = new ListNode(7);
  ListNode* c3 = new ListNode(8);
  c0->next = c1;
  c1->next = c2;
  c2->next = c3;

  ListNode* d0 = new ListNode(0);
  ListNode* d1 = new ListNode(6);
  ListNode* d2 = new ListNode(9);
  ListNode* d3 = new ListNode(10);
  d0->next = d1;
  d1->next = d2;
  d2->next = d3;

  vector<ListNode*> lists;
  lists.resize(4);
  lists[0] = a0;
  lists[1] = b0;
  lists[2] = c0;
  lists[3] = d0;
  ListNode* head = NULL; 
  Solution s;
  head = s.mergeKLists(lists);
  while (head != NULL)
  {
    cout<<head->val<<"  ";
    ListNode* t = head;
    head = head->next;
    delete t;
  }
  return 0;
}
