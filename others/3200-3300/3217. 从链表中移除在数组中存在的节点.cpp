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
    ListNode *modifiedList(vector<int> &nums, ListNode *head) {
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;

        ListNode dummy(0, head);
        ListNode *curr = head;
        ListNode *prev = &dummy;

        while (curr) {
            if (mp[curr->val]) {
                curr = curr->next;
                prev->next = curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return dummy.next;
    }
};