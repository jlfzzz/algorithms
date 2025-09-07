#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;


class Solution {
public:
    long long bowlSubarrays(vector<int> &nums) {
        int n = nums.size();
        vector<int> stk;
        int ans = 0;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            while (!stk.empty() && x > nums[stk.back()]) {
                if (stk.size() > 1) {
                    ans++;
                }
                stk.pop_back();
            }

            stk.push_back(i);
        }

        return ans;
    }
};
