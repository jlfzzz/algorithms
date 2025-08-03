#include <algorithm>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int pairSum(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;

        auto max = [](int a, int b) {
            return a > b ? a : b;
            };

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *right = reverse(slow);
        ListNode *left = head;
        int ans = 0;

        while (right) {
            int sum = right->val + left->val;
            left = left->next;
            right = right->next;
            ans = max(ans, sum);
        }
        return ans;
    }

    ListNode *reverse(ListNode *head) {
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