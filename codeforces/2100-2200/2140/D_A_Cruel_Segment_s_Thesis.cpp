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

    int ans = 0;
    vector<pii> vp;
    For(i, n) {
        int l, r;
        cin >> l >> r;
        ans += r - l;
        vp.emplace_back(l, r);
    }

    ranges::sort(vp, [](pii &a, pii &b) { return a.first + a.second < b.first + b.second; });

    if (n % 2 == 0) {
        int t = ans;
        for (int i = 0; i < n / 2; i++) {
            t += vp[n - 1 - i].first + vp[n - 1 - i].second - (vp[i].first + vp[i].second);
        }

        ans += t / 2;
    } else {
        int suf = 0, pre = 0;
        for (int i = 0; i < n / 2 + 1; i++) {
            pre += vp[i].first + vp[i].second;
        }
        for (int i = n / 2 + 1; i < n; i++) {
            suf += vp[i].first + vp[i].second;
        }
        int t = 0;
        for (int i = 0; i < n / 2 + 1; i++) {
            int temp_pre = pre - (vp[i].first + vp[i].second);
            t = max(t, suf - temp_pre + (ans - (vp[i].second - vp[i].first)));
        }
        pre -= vp[n / 2].first + vp[n / 2].second;
        suf += vp[n / 2].first + vp[n / 2].second;
        for (int i = n / 2 + 1; i < n; i++) {
            int temp_suf = suf - (vp[i].first + vp[i].second);
            t = max(t, temp_suf - pre + (ans - (vp[i].second - vp[i].first)));
        }
        ans += t / 2;
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
