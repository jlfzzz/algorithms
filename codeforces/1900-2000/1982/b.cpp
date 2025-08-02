#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}
long long t;
long long x, y, k;
void solve() {
    cin >> x >> y >> k;
    while (k > 0 && x != 1) {
        int s = min(k, y - (x % y));
        k -= s;
        x = x + s;
        // 一次性加到能被整除，节约时间
        while (x % y == 0)
            x /= y;
    }
    k %= (y - 1);
    x += k;
    // 因为前面是在x=1时就跳出了while
    // 所以可能少进行了几次操作
    if (x % y == 0)
        x /= y;
    // 前面操作完之后x可能能被y整除
    cout << x << endl;
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
