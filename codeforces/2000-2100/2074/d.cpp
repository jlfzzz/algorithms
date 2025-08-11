#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> pos(n);
    For(i, n) cin >> pos[i];
    vector<int> radius(n);
    For(i, n) cin >> radius[i];

    unordered_map<int, int> heights;
    For(i, n) {
        int r = radius[i];
        int p = pos[i];

        for (int j = p - r; j <= p + r; j++) {
            if (!heights.contains(j)) {
                heights[j] = floor(sqrt(r * r - (p - j) * (p - j)));
            } else {
                heights[j] = max(heights[j], (int) floor(sqrt(r * r - (p - j) * (p - j))));
            }
        }
    }

    int ans = 0;
    for (const auto &[p, h]: heights) {
        ans += 2 * h + 1;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
