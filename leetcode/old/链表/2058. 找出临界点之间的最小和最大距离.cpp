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
    vector<int> nodesBetweenCriticalPoints(ListNode *head) {
        vector<int> ans(2, -1);
        if (!head || !head->next || !head->next->next) return ans;
        ListNode dummy(0, head);
        ListNode *prev = head;
        ListNode *curr = head->next;
        vector<int> pos;
        int idx = 1;

        while (curr->next) {
            if (curr->val > prev->val && curr->val > curr->next->val ||
                curr->val < prev->val && curr->val < curr->next->val)
                pos.emplace_back(idx);

            prev = curr;
            curr = curr->next;
            idx++;
        }
        if (pos.size() < 2) return ans;
        ranges::sort(pos);
        int n = pos.size();
        int first = idx + 100;
        for (int i = 1; i < n; i++) {
            first = min(first, pos[i] - pos[i - 1]);
        }
        ans[0] = first;
        ans[1] = pos[n - 1] - pos[0];
        return ans;
    }
};