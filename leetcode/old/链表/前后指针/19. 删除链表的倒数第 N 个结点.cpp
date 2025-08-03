struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode dummy(0, head);
        ListNode *right = &dummy;
        for (int i = 0; i < n; i++)
            right = right->next;
        ListNode *left = &dummy;
        while (right->next) {
            right = right->next;
            left = left->next;
        }
        left->next = left->next->next;
        return dummy.next;

    }
};