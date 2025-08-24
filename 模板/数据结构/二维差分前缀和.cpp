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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int w;
    cin >> w;
    vector<int> heights(w);
    For(i, w) cin >> heights[i];

    vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));

    for (int i = 1; i + k - 1 <= n; i++) {
        for (int j = 1; j + k - 1 <= m; j++) {
            diff[i][j]++;
            diff[i][j + k]--;
            diff[i + k][j]--;
            diff[i + k][j + k]++;
        }
    }

    priority_queue<int> pq;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff[i][j] = diff[i][j] + diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            pq.push(diff[i][j]);
        }
    }

    ranges::sort(heights, greater<int>());

    int ans = 0;
    For(i, w) {
        if (pq.empty())
            break;
        int x = pq.top();
        pq.pop();
        ans += heights[i] * x;
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
