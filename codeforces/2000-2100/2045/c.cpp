#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    string s;
    cin >> s;
    string t;
    cin >> t;

    int ans_len = inf;
    string ans;

    vector<int> cnt(26, inf);
    for (int i = 0; i < t.size() - 1; i++) {
        cnt[t[i] - 'a'] = i;
    }

    int n = s.size();
    int m = t.size();
    for (int i = 1; i < n; i++) {
        int j = s[i] - 'a';
        if (cnt[j] != inf) {
            int l = i + m - cnt[j];
            if (l < ans_len) {
                ans_len = l;
                // cout << cnt[j] << endl;
                ans = s.substr(0, i) + t.substr(cnt[j]);
            }
        }
    }

    if (ans_len == inf) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
