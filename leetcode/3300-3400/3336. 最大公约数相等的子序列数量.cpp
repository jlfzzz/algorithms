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
    int subsequencePairCount(vector<int> &nums) {
        int n = SZ(nums);
        int mx = ranges::max(nums);
        vvi dp(mx + 1, vi(mx + 1, 0));

        dp[0][0] = 1;

        for (int x: nums) {
            vvi ndp = dp;

            F(i, 0, mx) {
                F(j, 0, mx) {
                    if (dp[i][j] == 0)
                        continue;

                    int g1 = gcd(i, x);
                    int g2 = j;
                    ndp[g1][g2] = (ndp[g1][g2] + dp[i][j]) % MOD;

                    g1 = i;
                    g2 = gcd(j, x);
                    ndp[g1][g2] = (ndp[g1][g2] + dp[i][j]) % MOD;
                }
            }
            dp = move(ndp);
        }

        ll ans = 0;
        F(i, 1, mx) { ans = (ans + dp[i][i]) % MOD; }

        return ans;
    }
};

class Solutio2n {
public:
    int subsequencePairCount(vector<int> &nums) {
        int n = SZ(nums);
        int m = 0;
        for (int x: nums)
            m = max(m, x);

        vl p2(n + 1), p3(n + 1);
        p2[0] = p3[0] = 1;
        F(i, 1, n) {
            p2[i] = p2[i - 1] * 2 % MOD;
            p3[i] = p3[i - 1] * 3 % MOD;
        }

        vi cnt(m + 1, 0);
        F(g, 1, m) {
            for (int x: nums) {
                if (x % g == 0) {
                    cnt[g]++;
                }
            }
        }

        vvl H(m + 1, vl(m + 1));

        D(i, m, 1) {
            D(j, m, 1) {
                if (cnt[i] == 0 || cnt[j] == 0) {
                    H[i][j] = 0;
                    continue;
                }

                ll lcm_val = (1LL * i * j) / std::gcd(i, j);
                int c12 = (lcm_val > m) ? 0 : cnt[lcm_val];
                int c1 = cnt[i] - c12;
                int c2 = cnt[j] - c12;

                ll term = p2[c1] * p2[c2] % MOD * p3[c12] % MOD;
                ll sub1 = p2[cnt[j]];
                ll sub2 = p2[cnt[i]];

                ll G = (term - sub1 - sub2 + 1) % MOD;
                if (G < 0)
                    G += MOD;

                ll sub_H = 0;
                for (int a = 1; a * i <= m; ++a) {
                    for (int b = 1; b * j <= m; ++b) {
                        if (a == 1 && b == 1)
                            continue;
                        sub_H = (sub_H + H[a * i][b * j]) % MOD;
                    }
                }

                H[i][j] = (G - sub_H + MOD) % MOD;
            }
        }

        ll ans = 0;
        F(g, 1, m) { ans = (ans + H[g][g]) % MOD; }

        return ans;
    }
};


// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
