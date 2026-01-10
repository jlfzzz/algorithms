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
    int maxStudents(vector<vector<char>> &a) {
        int n = SZ(a);
        int m = SZ(a[0]);

        int u = 1 << m;

        vector dp(n, vector(m, vvi(u, vi(2, -1))));

        auto dfs = [&](this auto &&dfs, int i, int j, int mask, int ul) -> int {
            if (i == n) {
                return 0;
            }

            int ni = i;
            int nj = j + 1;
            int nxt = (mask >> j) & 1;

            if (j == m - 1) {
                nj = 0;
                ni = i + 1;
                nxt = 0;
            }

            int &memo = dp[i][j][mask][ul];
            if (memo != -1) {
                return memo;
            }

            int res = dfs(ni, nj, mask & ~(1 << j), nxt);

            if (a[i][j] != '#') {
                bool bad = false;

                if (j > 0 && (mask & (1 << (j - 1))))
                    bad = true;

                if (j < m - 1 && (mask & (1 << (j + 1))))
                    bad = true;

                if (ul)
                    bad = true;

                if (!bad) {
                    res = max(res, 1 + dfs(ni, nj, mask | (1 << j), nxt));
                }
            }

            return memo = res;
        };

        return dfs(0, 0, 0, 0);
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
