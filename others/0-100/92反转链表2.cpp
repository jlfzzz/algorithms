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
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        ListNode dummy(0, head);
        int count = 1;
        ListNode *curr = head;
        ListNode *prev = &dummy;

        while (count < left) {
            prev = curr;
            curr = curr->next;
            count++;
        }

        ListNode *tempPrev = prev;
        while (count <= right) {
            ListNode *next = curr->next;
            curr->next = tempPrev;
            tempPrev = curr;
            curr = next;
            count++;
        }
        prev->next->next = curr;
        prev->next = tempPrev;

        return dummy.next;
    }
};