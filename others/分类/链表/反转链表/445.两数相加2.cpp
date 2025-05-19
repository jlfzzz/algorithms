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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head1 = reverse(l1);
        ListNode *head2 = reverse(l2);

        ListNode *next = nullptr;
        int carry = 0;

        while (carry || head1 || head2) {
            int sum = carry;
            if (head1) {
                sum += head1->val;
                head1 = head1->next;
            }

            if (head2) {
                sum += head2->val;
                head2 = head2->next;
            }

            carry = sum / 10;
            sum = sum % 10;

            ListNode *curr = new ListNode(sum, next);
            next = curr;
        }
        return next;
    }

    static ListNode *reverse(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

int main(void) {
    ListNode dummy1(0, nullptr);
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    dummy1.next = node1;
    dummy1.next->next = node2;

    ListNode *curr = dummy1.next;
    while (curr) {
        std::cout << curr->val << std::endl;
        curr = curr->next;
    }

    ListNode *last = Solution::reverse(dummy1.next);

    curr = last;
    while (curr) {
        std::cout << curr->val << std::endl;
        curr = curr->next;
    }
    return 0;
}