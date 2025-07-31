#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fori(n) for (int i = 0; i < (n); ++i)
#define ford(n) for (int i = (n) - 1; i >= 0; --i)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<ll> nums(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    map<ll, vector<ll>> all;
    map<ll, ll> vis;

    auto dfs = [&](this auto &&dfs, ll x) -> ll {
        if (vis.contains(x)) {
            return vis[x];
        }
        // ll cnt = x;
        // for (ll v: all[x]) {
        //     cnt = max(cnt, dfs(x + v - 1));
        // }
        ll cnt = 0;
        for (ll v: all[x]) {
            cnt = max(cnt, dfs(x + v - 1) + v - 1);
        }
        vis[x] = cnt;
        return cnt;
    };

    for (int i = 1; i <= n; i++) {
        if (i == 1)
            continue;
        ll t = nums[i] - 1 + i - n;
        if (t >= 0) {
            // cout << t << '\n';
            all[t].push_back(i);
        }
    }

    cout << dfs(0) + n << '\n';
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
