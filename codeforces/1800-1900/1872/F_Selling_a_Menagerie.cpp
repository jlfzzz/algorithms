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
    vector<int> a(n + 1), c(n + 1);
    vector<int> deg(n + 1);
    vector<int> b(n + 1);
    For(i, n) {
        int v;
        cin >> v;
        a[i + 1] = v;
        b[v] = i + 1;
        deg[v]++;
    }
    For(i, n) cin >> c[i + 1];

    vector<int> ans;

    deque<int> dq;
    vector<int> in(n + 1);
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            dq.push_back(i);
        }
    }

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        in[u] = 1;
        ans.push_back(u);

        deg[a[u]]--;
        if (deg[a[u]] == 0) {
            dq.push_back(a[u]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            vector<int> temp;
            auto dfs = [&](this auto &&dfs, int u) -> void {
                in[u] = 1;
                temp.push_back(u);
                if (!in[a[u]]) {
                    dfs(a[u]);
                }
            };

            dfs(i);

            int mn_idx = 0;
            for (int k = 1; k < temp.size(); k++) {
                if (c[temp[k]] < c[temp[mn_idx]])
                    mn_idx = k;
            }

            for (int k = mn_idx + 1; k < temp.size(); k++)
                ans.push_back(temp[k]);
            for (int k = 0; k <= mn_idx; ++k)
                ans.push_back(temp[k]);
        }
    }

    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
