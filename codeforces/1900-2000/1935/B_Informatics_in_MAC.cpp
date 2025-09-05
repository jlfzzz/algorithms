#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> pref(n), suf(n);
    vector<int> cnt(n + 1, 0);
    int mex = 0;
    For(i, n) {
        if (a[i] <= n)
            cnt[a[i]]++;
        while (mex <= n && cnt[mex] > 0)
            mex++;
        pref[i] = mex;
    }
    fill(cnt.begin(), cnt.end(), 0);
    mex = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] <= n)
            cnt[a[i]]++;
        while (mex <= n && cnt[mex] > 0)
            mex++;
        suf[i] = mex;
    }
    for (int i = 0; i + 1 < n; ++i) {
        if (pref[i] == suf[i + 1]) {
            cout << 2 << '\n';
            cout << 1 << ' ' << (i + 1) << '\n';
            cout << (i + 2) << ' ' << n << '\n';
            return;
        }
    }
    cout << -1 << '\n';
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
