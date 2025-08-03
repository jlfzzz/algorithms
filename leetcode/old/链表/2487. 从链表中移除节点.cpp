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

// 最好用递归和栈

class Solution {
public:
    ListNode *removeNodes(ListNode *head) {
        ListNode *curr = head;
        vector<int> record;
        int maxVal = 0;

        while (curr) {
            record.emplace_back(curr->val);
            curr = curr->next;
        }

        int n = record.size();
        vector<int> rightMax(n);
        for (int i = n - 1; i >= 0; i--) {
            maxVal = max(maxVal, record[i]);
            rightMax[i] = maxVal;
        }

        ListNode dummy(0, head);
        curr = head;
        ListNode *prev = &dummy;

        int idx = 0;
        while (curr) {
            if (rightMax[idx] > curr->val) {
                curr = curr->next;
                prev->next = curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
            idx++;
        }

        return dummy.next;
    }
};