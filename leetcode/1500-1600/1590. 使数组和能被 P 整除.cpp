#include <bits/stdc++.h>
using ll = long long;
using namespace std;

class Solution {
public:
    int minSubarray(vector<int> &nums, int p) {
        int n = nums.size();
        ll sum = accumulate(nums.begin(), nums.end(), 0ll);

        int d = sum % p;
        if (d == 0) {
            return 0;
        }

        ll pre = 0;
        unordered_map<int, int> pos;
        pos[0] = -1;
        int ans = n;

        for (int i = 0; i < n; i++) {
            pre += nums[i];
            pre %= p;
            int target = (pre - d + p) % p;
            if (pos.count(target)) {
                ans = min(ans, i - pos[target]);
            }

            pos[pre] = i;
        }

        return ans == n ? -1 : ans;
    }
};
