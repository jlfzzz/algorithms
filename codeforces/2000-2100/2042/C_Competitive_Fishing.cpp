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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector<int> suf(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + (s[i] == '1' ? 1 : -1);
    }

    vector<int> contrib;
    for (int i = 0; i < n - 1; i++) {
        contrib.push_back(suf[i + 1]);
    }

    sort(contrib.begin(), contrib.end(), greater<>());

    int cur = 0;
    int cuts = 0;
    for (int g: contrib) {
        if (cur >= k)
            break;
        if (g <= 0)
            break;
        cur += g;
        cuts++;
    }

    if (cur < k) {
        cout << -1 << '\n';
        return;
    }
    cout << cuts + 1 << '\n';
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
