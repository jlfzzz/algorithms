#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

bool fff = false;
vector<vector<int>> mult(70005);
void init() {
    if (!fff) {
        for (int i = 1; i < 70005; i++) {
            for (int j = i; j < 70005; j += i) {
                mult[j].push_back(i);
            }
        }
    }
    fff = true;
}

class Solution {
public:
    int totalBeauty(vector<int> &nums) {
        init();
        int n = nums.size();
        int mx = ranges::max(nums);
        vector<ll> dp(mx + 1);
        vector<vector<int>> pos(mx + 1, vector<int>());

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int y: mult[x]) {
                if (y > mx)
                    break;
                pos[y].push_back(i);
            }
        }

        for (int g = 1; g <= mx; g++) {
            vector<int> temp;
            for (int idx: pos[g]) {
                temp.push_back(nums[idx]);
            }

            auto temp2 = temp;
            ranges::sort(temp2);
            temp2.erase(unique(temp2.begin(), temp2.end()), temp2.end());
            int sz = temp2.size();
            vector<ll> tree(sz + 1);

            auto add = [&](int i, ll val) -> void {
                for (; i <= sz; i += i & -i) {
                    tree[i] = (tree[i] + val) % MOD;
                }
            };

            auto query = [&](int i) {
                ll res = 0;
                while (i) {
                    res = (res + tree[i]) % MOD;
                    i -= i & -i;
                }
                return res;
            };

            for (int val: temp) {
                int i = ranges::lower_bound(temp2, val) - temp2.begin();
                ll t = query(i);
                // res = (1ll + res + t) % MOD;
                add(i + 1, t + 1);
            }
            dp[g] = query(sz);
        };

        ll ans = 0;
        for (int i = mx; i >= 1; i--) {
            for (int j = i + i; j <= mx; j += i) {
                dp[i] = (dp[i] - dp[j] + MOD) % MOD;
            }
            ans = (ans + dp[i] * i) % MOD;
        }
        return ans;
    }
};
