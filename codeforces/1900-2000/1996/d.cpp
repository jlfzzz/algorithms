#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n, x, ans = 0;
    cin >> n >> x;
    for (int a = 1; a < x; a++) {
        for (int b = 1; b < x; b++) {
            if (a * b > n) {
                break;
            }
            int c = max(0, min(x - a - b, (n - a * b) / (a + b)));
            ans += c;
        }
    }
    cout << ans << "\n";
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
