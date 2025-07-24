#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// iteration
class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = NULL;
        ListNode *current = head;

        while (current) {
            ListNode *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};

//recursion
class SolutionRecursion {
public:
    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *last = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return last;
    }

    
};