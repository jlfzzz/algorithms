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
    // 206. 反转链表
    ListNode *reverseList(ListNode *head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur) {
            ListNode *nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }

public:
    vector<int> nextLargerNodes(ListNode *head) {
        head = reverseList(head);
        vector<int> ans;
        stack<int> st; // 单调栈（节点值）
        for (auto cur = head; cur; cur = cur->next) {
            while (!st.empty() && st.top() <= cur->val)
                st.pop(); // 弹出无用数据
            // 栈顶就是第 i 个节点的下一个更大元素
            ans.push_back(st.empty() ? 0 : st.top());
            st.push(cur->val);
        }
        // 由于是倒着记录答案的，返回前要把答案反转
        reverse(ans.begin(), ans.end());
        return ans;
    }
};