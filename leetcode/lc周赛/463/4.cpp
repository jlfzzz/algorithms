#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;


ll q_pow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

class Solution {
public:
    int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
        int n = nums.size();
        int B = sqrt(n) + 1;
        vector<ll> f(n, 1);
        unordered_map<ll, vector<int>> d;

        auto get_key = [&](int k, int offset) { return (1LL * k << 20) | offset; };

        for (auto &q: queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            if (k > B) {
                for (int i = l; i <= r; i += k)
                    f[i] = 1LL * f[i] * v % MOD;
            } else {
                int offset = l % k;
                ll kk = get_key(k, offset);
                if (!d.count(kk))
                    d[kk].assign(n / k + 10, 1);
                int left = (l - offset) / k, right = (r - offset) / k;
                d[kk][left] = 1LL * d[kk][left] * v % MOD;
                d[kk][right + 1] = 1LL * d[kk][right + 1] * q_pow(v, MOD - 2) % MOD;
            }
        }

        for (auto &[kk, v]: d) {
            int k = kk >> 20, offset = kk & ((1 << 20) - 1);
            for (int i = 1; i < v.size(); i++)
                v[i] = 1LL * v[i] * v[i - 1] % MOD;
            for (int i = 0, pos = offset; i < v.size() && pos < n; i++, pos += k)
                f[pos] = 1LL * f[pos] * v[i] % MOD;
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
            nums[i] = 1LL * nums[i] * f[i] % MOD;
        for (int x: nums) {
            ans ^= x;
        }
        return ans;
    }
};
