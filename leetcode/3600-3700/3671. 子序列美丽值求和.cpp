#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

template<typename T = long long>
class BIT {
    vector<T> tree;

public:
    BIT(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

class Solution {
public:
    int totalBeauty(vector<int> &nums) {
        int mx = 0;
        for (int x: nums) {
            mx = max(mx, x);
        }

        vector<vector<int>> groups(mx + 1);
        for (int x: nums) {
            for (int d = 1; d * d <= x; ++d) {
                if (x % d == 0) {
                    groups[d].push_back(x);
                    if (d * d != x) {
                        groups[x / d].push_back(x);
                    }
                }
            }
        }

        vector<long long> cnt(mx + 1, 0);
        BIT<long long> bit(mx + 1);

        for (int g = 1; g <= mx; g++) {
            if (groups[g].empty())
                continue;

            vector<pair<long long, long long>> temp;

            for (int x: groups[g]) {
                long long c = bit.pre(x - 1) % MOD;

                long long val = (c + 1) % MOD;

                cnt[g] = (cnt[g] + val) % MOD;

                bit.update(x, val);
                temp.push_back({x, val});
            }

            for (auto &p: temp) {
                bit.update(p.first, -p.second);
            }
        }

        long long ans = 0;
        for (int g = mx; g >= 1; g--) {
            if (cnt[g] == 0)
                continue;

            long long c = cnt[g];
            for (int k = 2 * g; k <= mx; k += g) {
                c = (c - cnt[k] + MOD) % MOD;
            }

            cnt[g] = c;

            ans = (ans + c * g) % MOD;
        }

        return ans;
    }
};

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

class Solution2 {
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
