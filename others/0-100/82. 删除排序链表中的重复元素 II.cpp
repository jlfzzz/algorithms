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
        ListNode dummy(0, head);
        ListNode *curr = dummy.next;
        ListNode *prev = &dummy;
        while (curr && curr->next) {
            ListNode *next = curr->next;
            if (next->val == curr->val) {
                while (next->next && next->next->val == curr->val) {
                    next = next->next;
                }
                prev->next = next->next;
                curr = next->next;
            } else {
                prev = curr;
                curr = next;
            }
            
        }
        return dummy.next;
    }
};