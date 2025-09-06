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
    int n, q;
    cin >> n >> q;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n - 1; j++) {
            a[i][j] = (s[i][j - 1] == '.' && s[i][j] == '.' && s[i + 1][j - 1] == '.' && s[i + 1][j] == '.');
        }
    }

    vector<vector<int>> ps(n, vector<int>(n));
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n - 1; j++) {
            ps[i][j] = a[i][j] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
        }
    }

    while (q--) {
        int U, D, L, R;
        cin >> U >> D >> L >> R;
        int r1 = U, r2 = D - 1, c1 = L, c2 = R - 1;
        if (r1 > r2 || c1 > c2) {
            cout << 0 << '\n';
            continue;
        }
        int ans = ps[r2][c2] - ps[r1 - 1][c2] - ps[r2][c1 - 1] + ps[r1 - 1][c1 - 1];
        cout << ans << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
