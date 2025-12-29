#include <bits/stdc++.h>
using namespace std;
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
    int numberOfCombinations(string num) {
        int n = SZ(num);

        vvi lcp(n + 1, vi(n + 1, 0));
        D(i, n - 1, 0) {
            D(j, n - 1, 0) {
                if (num[i] == num[j]) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                } else {
                    lcp[i][j] = 0;
                }
            }
        }

        vvl pre(n + 1, vl(n + 1, 0));

        F(i, 1, n) {
            F(len, 1, i) {
                int L = i - len;

                if (num[L] == '0') {
                    pre[i][len] = pre[i][len - 1];
                    continue;
                }

                ll sum = 0;

                if (L == 0) {
                    sum = 1;
                } else {
                    sum = pre[L][min(len - 1, L)];

                    if (L >= len) {
                        int LL = L - len;

                        int prefix = lcp[LL][L];
                        bool ok = false;

                        if (prefix >= len) {
                            ok = true;
                        } else if (num[LL + prefix] < num[L + prefix]) {
                            ok = true;
                        }

                        if (ok) {
                            ll t = (pre[L][len] - pre[L][len - 1] + MOD) % MOD;
                            sum = (sum + t) % MOD;
                        }
                    }
                }

                pre[i][len] = (pre[i][len - 1] + sum) % MOD;
            }
        }

        return pre[n][n];
    }
};
