#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int mx = *max_element(a.begin(), a.end());
    vector<int> pos;
    For(i, n) {
        if (a[i] == mx) {
            pos.push_back(i);
        }
    }

    vector<int> dp1(n + 1), dp2(n + 1);

    vector<pii> L, R;
    // 存第一个的索引
    {
        int mn = -inf;
        For(i, n) {
            if (a[i] > mn) {
                L.emplace_back(a[i], i);
                mn = a[i];
            }
        }
    }

    {
        int mn = -inf;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > mn) {
                R.emplace_back(a[i], i);
                mn = a[i];
            }
        }
    }

    int m = pos.size();


    {
        dp2[n] = 1;
        int sz = R.size();
        int idx = sz - 1;
        for (int i = n - 1; i >= 0; i--) {
            int cur = a[i];
            if (cur < R[idx].first) {
                dp2[i] = dp2[i + 1] * 2 % MOD;
            } else {
                int lim = (idx + 1 < sz) ? R[idx + 1].second : n;
                int cnt = 0;
                for (int j = i + 1; j <= lim; j++) {
                    cnt = (cnt + dp2[j]) % MOD;
                }
                dp2[i] = cnt;
            }
        }
    }

    int sz = L.size();
    dp1[0] = 1;
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
