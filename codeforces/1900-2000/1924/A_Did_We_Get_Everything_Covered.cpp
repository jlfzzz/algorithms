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
    int n, k, m;
    cin >> n >> k >> m;
    set<char> cnt;
    string s;
    cin >> s;

    string ans;

    for (int i = 0; i < m; i++) {
        char c = s[i];
        cnt.insert(c);
        if (cnt.size() == k) {
            ans += c;
            cnt.clear();
        }
    }

    if (ans.size() >= n) {
        cout << "YES\n";
    } else {
        for (int i = 1; i <= k; i++) {
            if (!cnt.contains((char) (i - 1 + 'a'))) {
                string t(n - ans.size(), (char) (i - 1 + 'a'));
                ans += t;
                cout << "NO\n";
                cout << ans << '\n';
                break;
            }
        }
    }
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
