#include <bits/stdc++.h>
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
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> ans(n, -1);
    for (int i = y - 1; i < x; i++) {
        ans[i] = 1;
    }
    for (int i = y - 2; i >= 0; i--) {
        ans[i] = -ans[i + 1];
    }
    for (int i = x; i < n; i++) {
        ans[i] = -ans[i - 1];
    }
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
