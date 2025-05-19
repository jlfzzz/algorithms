#include <unordered_map>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::unordered_map<ListNode *, int> map;

        ListNode *current = head;
        while (current) {
            if (map.find(current) != map.end()) {
                // 找到环的入口点
                return current;
            }

            map[current] = 1;  // 值不重要，只是标记节点已访问
            current = current->next;
        }

        return nullptr;  // 没有环
    }
};

// 还有一种方法空间是O(1)的