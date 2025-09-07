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
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].first >> p[i].second;

    if (n == 1) {
        cout << "Yes\n";
        cout << p[0].second << " " << -p[0].first << " " << 0 << '\n';
        return;
    }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(idx.begin(), idx.end(), rng);

    int rounds = min(50ll, n);
    for (int t = 0; t < rounds; t++) {
        int i1 = idx[t];
        int i2 = idx[(t + 1) % n];

        if (p[i1] == p[i2]) {
            continue;
        }

        auto [x1, y1] = p[i1];
        auto [x2, y2] = p[i2];

        int dx = x2 - x1;
        int dy = y2 - y1;

        int a = dy;
        int b = -dx;
        int c = -(a * x1 + b * y1);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            auto [x, y] = p[i];
            if (a * x + b * y + c == 0) {
                cnt++;
            }
        }

        if (cnt * 2 >= n) {
            cout << "Yes\n";
            cout << a << " " << b << " " << c << '\n';
            return;
        }
    }

    cout << "No\n";
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
