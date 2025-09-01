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
    vector<int> minDifference(int n, int k) {
        vector<int> ans;
        for (int start = 1; start * start <= n; start++) {
            vector<int> temp;

            auto dfs = [&](this auto &&dfs, int rem, int cnt) -> void {
                if (cnt == k) {
                    if (rem != 1) {
                        return;
                    }

                    ranges::sort(temp);
                    int d = temp.back() - temp[0];
                    if (ans.empty()) {
                        ans = temp;
                    } else {
                        int ans_d = ans.back() - ans[0];
                        if (d < ans_d) {
                            ans = temp;
                        }
                    }
                    return;
                }

                for (int nxt = 1; nxt * nxt <= rem; nxt++) {
                    if (rem % nxt) {
                        continue;
                    }
                    temp.push_back(nxt);
                    dfs(rem / nxt, cnt + 1);
                    temp.pop_back();
                }
            };

            if (n % start) {
                continue;
            }
            temp.push_back(start);
            dfs(n / start, 1);
        }

        return ans;
    }
};

class Solution {
public:
    long long maxProduct(vector<int> &nums) {
        int maxv = 0;
        for (int x: nums)
            maxv = max(maxv, x);
        int m = 0;
        while ((1 << m) <= maxv)
            m++;
        if (m == 0)
            m = 1;
        int up = 1 << m;

        vector<int> mx(up, 0);
        for (int x: nums)
            mx[x] = max(mx[x], x);

        // SOS DP: mx[mask] = max value among all subsets of mask
        for (int i = 0; i < m; i++) {
            for (int mask = 0; mask < up; mask++) {
                if (mask & (1 << i)) {
                    mx[mask] = max(mx[mask], mx[mask ^ (1 << i)]);
                }
            }
        }

        ll ans = 0;
        for (int x: nums) {
            int mask = (~x) & (up - 1);
            ans = max(ans, 1LL * x * mx[mask]);
        }

        return ans;
    }
};

// class Solution {
// public:
//     vector<int> recoverOrder(vector<int> &order, vector<int> &friends) {
//         unordered_map<int, int> cnt;
//         int n = order.size();
//         for (int i = 0; i < n; i++) {
//             cnt[order[i]] = i;
//         }

//         vector<pii> ans;
//         for (int x: friends) {
//             int pos = cnt[x];
//             ans.emplace_back(pos, x);
//         }

//         ranges::sort(ans);
//         vector<int> ans2;
//         for (auto [a, b]: ans) {
//             ans2.push_back(b);
//         }
//         return ans2;
//     }
// };
