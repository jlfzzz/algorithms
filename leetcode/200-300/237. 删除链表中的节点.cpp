struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

// 浅拷贝
class Solution {
public:
    void deleteNode(ListNode *node) {
        *node = *node->next;
    }
};