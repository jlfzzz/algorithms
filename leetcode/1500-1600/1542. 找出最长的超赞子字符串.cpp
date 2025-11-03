#include <bits/stdc++.h>
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        unordered_map<int, int> cnt;
        cnt[0] = 0;
        int pre = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int j = s[i] - '0';
            pre ^= 1 << j;
            if (cnt.contains(pre)) {
                ans = max(ans, i - cnt[pre] + 1);
            }
            for (int k = 0; k < 10; k++) {
                int t = pre ^ (1 << k);
                if (cnt.contains(t)) {
                    ans = max(ans, i - cnt[t] + 1);
                }
            }

            if (!cnt.contains(pre)) {
                cnt[pre] = i;
            }
        }

        return ans;
    }
};
