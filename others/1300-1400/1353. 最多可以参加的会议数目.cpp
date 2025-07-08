#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxEvents(vector<vector<int>> &events) {
        ranges::sort(events);
        priority_queue<int, vector<int>, greater<int>> pq;
        int maxDay = 0;
        for (int i = 0; i < events.size(); i++) {
            maxDay = max(maxDay, events[i][1]);
        }
        int ans = 0;
        int j = 0;
        int n = events.size();
        for (int i = events[0][0]; i <= maxDay; ++i) {
            // 把今天开始的活动加入队列
            while (j < n && events[j][0] <= i) {
                pq.emplace(events[j][1]);
                ++j;
            }
            // 移除所有已经过期的活动
            while (!pq.empty() && pq.top() < i) {
                pq.pop();
            }
            // 可以参加一个活动
            if (!pq.empty()) {
                pq.pop();
                ++ans;
            }
        }
        return ans;
    }
};