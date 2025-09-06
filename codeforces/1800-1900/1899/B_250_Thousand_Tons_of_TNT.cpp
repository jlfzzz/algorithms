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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    vector<int> pre(n + 1);
    For(i, n) pre[i + 1] = pre[i] + a[i];
    int ans = 0;

    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {

            auto f = [&](int d) -> int {
                vector<int> temp;
                for (int j = 0; j + d <= n; j += d) {
                    int diff = pre[j + d] - pre[j];
                    temp.push_back(diff);
                }
                ranges::sort(temp);
                return temp.back() - temp[0];
            };

            ans = max(ans, f(i));
            if (n / i != i) {
                ans = max(ans, f(n / i));
            }
        }
    }

    cout << ans << '\n';
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
