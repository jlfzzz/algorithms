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

    vector<pii> w(n);
    For(i, n) {
        int t;
        cin >> t;
        w[i] = {t, i};
    }

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> in(n + 1), out(n + 1);
    int ts = 0;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        in[u] = ++ts;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);
        }
        out[u] = ++ts;
    };

    dfs(1, -1);

    vector<int> tree(ts * 2);
    auto add = [&](int i) -> void {
        for (; i <= ts; i += i & -i) {
            tree[i]++;
        }
    };

    auto get = [&](int i) -> int {
        int res = 0;
        while (i) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    };

    ranges::sort(w);
    int i = n - 1;
    while (i >= 0) {
        int j = i;
        while (j >= 0 && w[j].first == w[i].first) {
            j--;
        }
        for (int k = i; k > j; k--) {
            auto [weight, id] = w[k];
            int t1 = in[id + 1], t2 = out[id + 1];

            int sum = get(t2 - 1) - get(t1);
            if (sum != n - i - 1) {
                cout << id + 1 << '\n';
                return;
            }
        }

        for (int k = i; k > j; k--) {
            auto [weight, id] = w[k];
            int t1 = in[id + 1], t2 = out[id + 1];

            add(t1);
        }

        i = j;
    }
    // add(in[w[n - 1].second + 1]);
    // for (int i = n - 2; i >= 0; i--) {
    //     auto [weight, id] = w[i];
    //     int t1 = in[id + 1], t2 = out[id + 1];

    //     // cout << "weight is: " << weight << " id is: " << id << '\n';

    //     int sum = get(t2 - 1) - get(t1);
    //     if (sum == n - i - 1) {
    //         add(t1);
    //     } else {
    //         cout << id + 1 << '\n';
    //         return;
    //     }
    // }

    cout << 0 << '\n';
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
