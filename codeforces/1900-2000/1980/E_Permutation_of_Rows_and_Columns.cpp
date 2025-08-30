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
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m));

    For(i, n) {
        For(j, m) { cin >> a[i][j]; }
    }
    For(i, n) {
        For(j, m) { cin >> b[i][j]; }
    }

    vector<set<int>> v1, v2;
    for (int row = 0; row < n; row++) {
        set<int> st1, st2;
        for (int col = 0; col < m; col++) {
            st1.insert(a[row][col]);
            st2.insert(b[row][col]);
        }

        v1.emplace_back(st1);
        v2.emplace_back(st2);
    }

    ranges::sort(v1), ranges::sort(v2);
    if (v1 != v2) {
        cout << "NO\n";
        return;
    }

    v1.clear(), v2.clear();
    for (int c = 0; c < m; c++) {
        set<int> st1, st2;
        for (int r = 0; r < n; r++) {
            st1.insert(a[r][c]);
            st2.insert(b[r][c]);
        }

        v1.emplace_back(st1);
        v2.emplace_back(st2);
    }
    ranges::sort(v1), ranges::sort(v2);
    if (v1 != v2) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
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
