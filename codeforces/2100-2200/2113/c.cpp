#include <bits/stdc++.h>
#include <functional>
#include <string>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<char>> grid(n, vector<char>(m));
    int total = 0;
    For(i, n) {
        For(j, m) {
            cin >> grid[i][j];
            if (grid[i][j] == 'g') {
                total++;
            }
        }
    }

    vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cnt = 0;
            if (grid[i - 1][j - 1] == 'g') {
                cnt++;
            }
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + cnt;
        }
    }

    int mn = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i - 1][j - 1] == '.') {
                mn = min(mn, pre[min(n, i + k - 1)][min(m, j + k - 1)] - pre[min(n, i + k - 1)][max(0, j - k)] -
                                 pre[max(0, i - k)][min(m, j + k - 1)] + pre[max(0, i - k)][max(0, j - k)]);
            }
        }
    }
    cout << total - mn << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
