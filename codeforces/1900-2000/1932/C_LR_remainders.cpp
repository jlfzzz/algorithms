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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    string s;
    cin >> s;

    int l = 0, r = n - 1;
    for (char c: s) {
        if (c == 'L') {
            l++;
        } else {
            r--;
        }
    }

    ranges::reverse(s);
    vector<int> ans;
    int t = 1;

    for (char c: s) {
        if (c == 'L') {
            l--;
            t *= a[l];
        } else {
            r++;
            t *= a[r];
        }
        t %= m;
        ans.push_back(t);
    }

    ranges::reverse(ans);
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
