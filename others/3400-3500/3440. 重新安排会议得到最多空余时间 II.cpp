#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
constexpr int MOD = int(1e9 + 7);
class Solution {
public:
    int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime) {
        int n = startTime.size();

        // 计算空位长度
        auto get = [&](int i) -> int {
            if (i == 0) {
                return startTime[0];
            }
            if (i == n) {
                return eventTime - endTime[n - 1];
            }
            return startTime[i] - endTime[i - 1];
            };

        // 有 n+1 个空位，计算前三大的空位在哪
        int a = 0, b = -1, c = -1;
        for (int i = 1; i <= n; i++) {
            int sz = get(i);
            if (sz > get(a)) {
                c = b; b = a; a = i;
            } else if (b < 0 || sz > get(b)) {
                c = b; b = i;
            } else if (c < 0 || sz > get(c)) {
                c = i;
            }
        }

        int ans = 0;
        // 枚举桌子
        for (int i = 0; i < n; i++) {
            int sz = endTime[i] - startTime[i];
            if (i != a && i + 1 != a && sz <= get(a) ||
                i != b && i + 1 != b && sz <= get(b) ||
                sz <= get(c)) { // 可以移出去
                ans = max(ans, get(i) + sz + get(i + 1));
            } else {
                ans = max(ans, get(i) + get(i + 1));
            }
        }
        return ans;
    }
};

class Solution {
public:
    int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime) {
        int n = startTime.size();
        vector free(n + 1, 0);
        free[0] = startTime[0];
        for (int i = 0; i < n - 1; ++i) {
            free[i + 1] = startTime[i + 1] - endTime[i];
        }
        free[n] = eventTime - endTime.back();
        vector rightMax(n + 1, INT_MIN);
        for (int i = n - 1; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], free[i + 1]);
        }
        vector leftMax(n + 1, INT_MIN);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int diff = endTime[i] - startTime[i];
            int left = i - 1 >= 0 ? leftMax[i - 1] : 0;
            int right = rightMax[i + 1];
            ans = max(ans, free[i] + free[i + 1]);
            if (left >= diff || right >= diff) {
                ans = max(ans, free[i] + free[i + 1] + diff);
            }
            leftMax[i] = max((i - 1 >= 0 ? leftMax[i - 1] : INT_MIN), free[i]);
        }
        return ans;
    }
};