#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    --x;
    --y;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
        ans[(x + i) % n] = i % 2;
    if (n % 2 || (x - y) % 2 == 0)
        ans[x] = 2;
    for (auto x: ans)
        cout << x << ' ';
    cout << endl;
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
