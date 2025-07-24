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
    ListNode *insertGreatestCommonDivisors(ListNode *head) {
        if (!head->next) return head;

        ListNode *curr = head;
        while (curr->next) {
            ListNode *nxt = curr->next;
            int value = gcd(curr->val, nxt->val);
            ListNode *node = new ListNode(value);
            curr->next = node;
            node->next = nxt;

            curr = curr->next->next;
        }

        return head;
    }
};