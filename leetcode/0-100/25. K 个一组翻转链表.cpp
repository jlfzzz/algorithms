#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode dummy(0, head);
        ListNode *start = &dummy;
        ListNode *curr = &dummy;

        while (1) {
            int count = 0;
            while (count < k && curr->next) {
                curr = curr->next;
                count++;
            }

            if (count < k) {
                break;
            } else {
                ListNode *oldFirst = start->next;
                reverse(start, k);
                start = oldFirst;
                curr = start;
            }
        }
        return dummy.next;
    }

    void reverse(ListNode *dummy, int k) {
        ListNode *curr = dummy->next;
        ListNode *first = dummy->next;
        ListNode *prev = dummy;

        while (k > 0) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;

            k--;
        }
        dummy->next = prev;
        first->next = curr;

    }
};