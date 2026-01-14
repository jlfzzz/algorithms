#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

class Solution {
public:
    int calc(int x) {
        int res = 0;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                res++;
                while (x % i == 0)
                    x /= i;
            }
        }
        if (x > 1)
            res++;
        return res;
    }

    ll qpow(ll a, ll b) {
        ll res = 1;
        a %= MOD;
        while (b) {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int maximumScore(vector<int> &nums, int k) {
        int n = SZ(nums);
        vi vals(n);

        F(i, 0, n - 1) { vals[i] = calc(nums[i]); }

        vi l(n, -1), r(n, n);
        stack<int> stk;

        F(i, 0, n - 1) {
            while (!stk.empty() && vals[stk.top()] < vals[i]) {
                stk.pop();
            }
            if (!stk.empty())
                l[i] = stk.top();
            stk.push(i);
        }

        while (!stk.empty()) {
            stk.pop();
        }

        D(i, n - 1, 0) {
            while (!stk.empty() && vals[stk.top()] <= vals[i]) {
                stk.pop();
            }
            if (!stk.empty())
                r[i] = stk.top();
            stk.push(i);
        }

        vp vec;
        F(i, 0, n - 1) {
            ll cnt = 1ll * (i - l[i]) * (r[i] - i);
            vec.pb(nums[i], cnt);
        }

        sort(all(vec), [](pii &a, pii &b) { return a.fi > b.fi; });

        ll ans = 1;
        for (auto &[val, cnt]: vec) {
            if (cnt >= k) {
                ans = ans * qpow(val, k) % MOD;
                break;
            } else {
                ans = ans * qpow(val, cnt) % MOD;
                k -= cnt;
            }
        }

        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
