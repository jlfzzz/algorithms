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
    string s;
    cin >> s;

    map<int, int> cnt;
    for (char c: s) {
        cnt[c - '0']++;
    }

    if (cnt.size() == 1) {
        cout << -1 << '\n';
        return;
    }

    int ans = 0;
    if (cnt.size() > 2) {
        ans = 4;
    } else {
        auto it = cnt.begin();
        int t = it->second;
        if (t == 1 || t == 3) {
            ans = 6;
        } else {
            ans = 4;
        }
    }

    cout << ans << '\n';
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
