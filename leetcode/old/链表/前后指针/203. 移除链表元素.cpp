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
    ListNode *removeElements(ListNode *head, int val) {
        ListNode dummy(0, head);
        ListNode *fast = dummy.next;
        ListNode *prev = &dummy;
        while (fast) {
            ListNode *next = fast->next;
            if (fast->val == val) {
                prev->next = next;
                
            } else {
                prev = fast;
            }
            fast = next;
        }
        return dummy.next;
    }
};