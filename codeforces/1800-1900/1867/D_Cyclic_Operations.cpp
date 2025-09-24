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
    int n, k;
    cin >> n >> k;
    vector<int> b(n + 1);

    For(i, n) cin >> b[i + 1];

    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            if (b[i] != i) {
                cout << "NO\n";
                return;
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            if (b[i] == i) {
                cout << "NO\n";
                return;
            }
        }

        vector<int> vis(n + 1), deg(n + 1);
        for (int i = 1; i <= n; i++) {
            deg[b[i]]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 1;
            deg[b[u]]--;
            if (deg[b[u]] == 0) {
                q.push(b[u]);
            }
        }

        for (int i = 1; i <= n; i++) {
            if (vis[i]) {
                continue;
            }

            int cnt = 0;
            int t = i;
            while (!vis[t]) {
                vis[t] = 1;
                cnt++;
                t = b[t];
            }

            if (cnt != k) {
                cout << "NO\n";
                return;
            }
        }
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
