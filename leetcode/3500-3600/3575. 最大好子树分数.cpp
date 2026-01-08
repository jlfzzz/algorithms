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
    int goodSubtreeSum(vector<int> &vals, vector<int> &par) {
        int n = SZ(vals);
        vvi g(n);

        F(i, 1, n - 1) { g[par[i]].pb(i); }

        ll ans = 0;
        int U = 1 << 10;

        auto dfs = [&](this auto &&dfs, int u) -> vl * {
            vl *dp = new vl(U, -1);

            (*dp)[0] = 0;

            vi tcnt(10);
            string s1 = to_string(vals[u]);
            for (char ch: s1) {
                tcnt[ch - '0']++;
            }

            int ok = 1;
            for (int x: tcnt) {
                if (x > 1) {
                    ok = 0;
                    break;
                }
            }

            if (ok) {
                int mask = 0;
                F(i, 0, 9) {
                    if (tcnt[i]) {
                        mask |= 1 << i;
                    }
                }
                (*dp)[mask] = vals[u];
            }

            for (int v: g[u]) {
                vl *temp = dfs(v);
                vl ndp = *dp;

                D(mask, U - 1, 1) {
                    for (int sub = mask; sub >= 0; sub = (sub - 1) & mask) {
                        int other = mask ^ sub;
                        if ((*dp)[sub] != -1 && (*temp)[other] != -1) {
                            ndp[mask] = max(ndp[mask], (*dp)[sub] + (*temp)[other]);
                        }
                        if (sub == 0) {
                            break;
                        }
                    }
                }
                *dp = ndp;
                delete temp;
            }

            ll mx = 0;
            for (ll val: *dp) {
                mx = max(mx, val);
            }
            ans = (ans + mx) % MOD;

            return dp;
        };

        dfs(0);

        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
