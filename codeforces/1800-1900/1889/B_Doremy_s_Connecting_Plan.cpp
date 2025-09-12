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
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<pii> temp;
    for (int i = 1; i < n; i++) {
        temp.emplace_back(c * (i + 1) - a[i], i);
    }

    ranges::sort(temp);
    int sum = a[0];
    for (auto &[v, i]: temp) {
        if (sum + a[i] < (i + 1) * c) {
            cout << "No\n";
            return;
        }
        sum += a[i];
    }

    cout << "Yes\n";
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
