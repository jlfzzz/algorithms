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

ll val[N];
int init = [] {
    for (ll &i: val) {
        i = 1;
    }

    for (int i = 2; i < N; i++) {
        int t = i;
        for (int j = 2; j * j <= t; j++) {
            if (t % j == 0) {
                int cnt = 0;
                while (t % j == 0) {
                    cnt++;
                    t /= j;
                }

                cnt &= 1;
                if (cnt) {
                    val[i] *= j;
                }
            }
        }

        if (t) {
            val[i] *= t;
        }
    }

    return 0;
}();

class Solution {
public:
    using ll = long long;
    long long sumOfAncestors(int n, vector<vector<int>> &edges, vector<int> &nums) {
        vector<vector<int>> g(n);
        for (auto &e: edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        unordered_map<int, int> cnt;
        ll ans = 0;

        auto dfs = [&](this auto &&dfs, int x, int fa) -> void {
            int c = val[nums[x]];
            ans += cnt[c];
            cnt[c]++;
            for (int y: g[x]) {
                if (y != fa) {
                    dfs(y, x);
                }
            }
            cnt[c]--;
        };

        dfs(0, -1);
        return ans;
    }
};
