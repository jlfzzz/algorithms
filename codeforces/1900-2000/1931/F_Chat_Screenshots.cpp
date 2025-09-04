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


    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> deg(n + 1);
    For(i, k) {
        vector<int> temp(n);
        For(j, n) cin >> temp[j];
        for (int j = 1; j < n - 1; j++) {
            g[temp[j]].push_back(temp[j + 1]);
            deg[temp[j + 1]]++;
        }
    }

    if (n == 1 || k == 1) {
        cout << "YES\n";
        return;
    }

    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
            cnt++;
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int v: g[x]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
                cnt++;
            }
        }
    }


    if (cnt == n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
