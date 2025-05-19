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
    ListNode *swapPairs(ListNode *head) {
        ListNode dummy(0, head);
        ListNode *start = &dummy;
        ListNode *current = &dummy;

        while (1) {
            int count = 0;

            for (int i = 0; i < 2; i++) {
                if (current->next) {
                    current = current->next;
                } else {
                    return dummy.next;
                }
            }

            ListNode *first = start->next;
            ListNode *curr = first;
            ListNode *prev = start;

            for (int i = 0; i < 2; i++) {
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            start->next = prev;
            first->next = curr;

            start = first;
            current = first;
        }
    }
};