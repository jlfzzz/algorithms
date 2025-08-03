#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n + 1);
    For(i, n) { cin >> nums[i + 1]; }
    vector<int> pa(n + 1);
    pa[1] = 1;
    For(i, n - 1) { cin >> pa[i + 2]; }

    vector<vector<int>> g(n + 1, vector<int>());
    for (int i = 2; i <= n; i++) {
        g[pa[i]].push_back(i);
    }

    auto dfs = [&](this auto &&dfs, int i, int fa) -> int {
        int mn_child = INT_MAX;
        int curr = nums[i];
        for (int v: g[i]) {
            if (v != fa) {
                int t = dfs(v, i);
                mn_child = min(mn_child, t);
            }
        }
        if (i == 1) {
            return mn_child;
        }
        if (mn_child == INT_MAX) {
            return curr;
        } else {
            if (mn_child <= curr) {
                return mn_child;
            } else if (mn_child - 1 == curr) {
                return curr;
            } else {
                return curr + (mn_child - curr) / 2;
            }
        }
    };
    int mn = dfs(1, -1);
    int root = nums[1];
    int ans = root + mn;
    cout << ans << '\n';
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
