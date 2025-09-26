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

    string t = "Kato_Shoko";
    map<char, int> cnt1, cnt2;
    for (char c: t) {
        cnt1[c]++;
    }

    for (char c: s) {
        cnt2[c]++;
    }

    int ans = 0;
    for (auto &[c, cnt]: cnt2) {
        if (!cnt1.contains(c)) {
            ans += cnt;
        }
    }

    for (auto &[c, cnt]: cnt1) {
        if (cnt2.contains(c)) {
            if (cnt2[c] < cnt) {
                cout << "NO\n";
                return;
            }
            ans += cnt2[c] - cnt;
        } else {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES " << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
