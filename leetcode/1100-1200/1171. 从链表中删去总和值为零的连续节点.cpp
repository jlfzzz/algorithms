#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeZeroSumSublists(ListNode *head) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        int prefix = 0;
        unordered_map<int, ListNode *> seen;
        for (ListNode *node = dummy; node; node = node->next) {
            prefix += node->val;
            seen[prefix] = node;
        }
        prefix = 0;
        for (ListNode *node = dummy; node; node = node->next) {
            prefix += node->val;
            node->next = seen[prefix]->next;
        }
        return dummy->next;
    }
};

class Solution {
public:
    ListNode *removeZeroSumSublists(ListNode *head) {
        if (!head) return nullptr;

        int sum = 0;
        for (ListNode *p = head; p != nullptr; p = p->next) {
            sum += p->val;
            if (sum == 0) {
                return removeZeroSumSublists(p->next);
            }
        }

        head->next = removeZeroSumSublists(head->next);
        return head;
    }
};
