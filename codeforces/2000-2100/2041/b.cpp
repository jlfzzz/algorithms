#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int w, b;
    cin >> w >> b;
    w += b;
    int ans = 1;
    while (w >= ans) {
        w -= ans;
        ans++;
    }
    cout << ans - 1 << '\n';
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
