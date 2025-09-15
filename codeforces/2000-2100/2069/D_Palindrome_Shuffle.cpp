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
    int n = s.size();
    int l = 0, r = n - 1;
    while (l < r && s[l] == s[r]) {
        l++;
        r--;
    }
    if (l > r) {
        cout << "0\n";
        return;
    }
    s = s.substr(l, r - l + 1);
    n = s.size();
    l = n / 2 - 1, r = n / 2;
    while (l >= 0 && s[l] == s[r]) {
        l--;
        r++;
    }
    string L = s.substr(0, l + 1);
    string R = s.substr(r);
    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    if (L == R) {
        cout << l + 1 << '\n';
        return;
    }

    int ans = n;
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> pos(26);
        int res = 0;
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'].push_back(i);
        }
        for (vector<int> &v: pos) {
            if (v.empty())
                continue;
            res = max(res, v[v.size() / 2 - 1] + 1);
        }
        ans = min(ans, res);
        reverse(s.begin(), s.end());
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
