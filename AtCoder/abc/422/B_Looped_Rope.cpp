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
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i = 0; i < H; i++)
        cin >> grid[i];

    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '#') {
                int cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && ni < H && nj >= 0 && nj < W && grid[ni][nj] == '#') {
                        cnt++;
                    }
                }
                if (cnt != 2 && cnt != 4) {
                    cout << "No\n";
                    return;
                }
            }
        }
    }
    cout << "Yes\n";
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
