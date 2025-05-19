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
    ListNode *swapNodes(ListNode *head, int k) {
        if (!head->next) return head;

        int count = 1;
        ListNode *curr = head;
        while (curr->next) {
            curr = curr->next;
            count++;
        }

        curr = head;
        for (int i = 1; i < k; i++) {
            curr = curr->next;
        }
        ListNode *first = curr;
        curr = head;
        for (int i = 1; i < count - k + 1; i++) {
            curr = curr->next;
        }

        int value = curr->val;
        curr->val = first->val;
        first->val = value;

        return head;
    }
};