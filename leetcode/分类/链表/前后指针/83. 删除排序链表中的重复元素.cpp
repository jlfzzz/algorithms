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
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *curr = head;
        while (curr && curr->next) {
            if (curr->val == curr->next->val) {
                ListNode *next = curr->next;
                while (next && next->val == curr->val)
                    next = next->next;
                curr->next = next;
                curr = next;
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
};