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
    string s;
    cin >> s;

    int cw = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            cw++;
        }
    }

    int half = cw / 2;
    bool ok =
        (cw % 2 == 0) && (count(s.begin(), s.begin() + half, 'R') == 0) && (count(s.end() - half, s.end(), 'W') == 0);
    cout << (ok ? "YES" : "NO") << '\n';
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
