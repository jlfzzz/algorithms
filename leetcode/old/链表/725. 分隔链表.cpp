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
    vector<ListNode *> splitListToParts(ListNode *head, int k) {
        vector<ListNode *> ans(k, nullptr);

        // 计算链表长度
        ListNode *curr = head;
        int count = 0;
        while (curr) {
            count++;
            curr = curr->next;
        }

        int parts = count / k;
        int extra = count % k;

        curr = head;
        for (int i = 0; i < k && curr; i++) {
            ans[i] = curr;

            // 计算当前部分的长度
            int partSize = parts + (i < extra ? 1 : 0);

            // 移动到当前部分的末尾
            for (int j = 0; j < partSize - 1; j++) {
                curr = curr->next;
            }

            // 断开链表
            ListNode *next = curr->next;
            curr->next = nullptr;
            curr = next;
        }

        return ans;
    }
};