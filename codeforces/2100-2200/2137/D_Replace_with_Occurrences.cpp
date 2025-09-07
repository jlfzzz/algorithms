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
    vector<int> b(n);
    For(i, n) cin >> b[i];

    map<int, int> cnt;
    for (int x: b) {
        cnt[x]++;
    }

    int sum = 0;
    for (auto &[k, v]: cnt) {
        sum += v;
        if (v % k != 0) {
            cout << -1 << '\n';
            return;
        }
    }

    if (sum != n) {
        cout << -1 << '\n';
        return;
    }

    vector<int> ans(n);
    int curr = 1;

    map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
        int x = b[i];
        pos[x].push_back(i);
    }

    for (auto &[k, v]: pos) {
        for (int i = 0; i < v.size(); i += k) {
            for (int j = 0; j < k; j++) {
                int idx = i + j;
                ans[v[idx]] = curr;
            }
            curr++;
        }
    }

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
