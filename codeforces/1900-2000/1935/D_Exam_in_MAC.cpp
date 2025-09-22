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
    int n, c;
    cin >> n >> c;

    vector<int> s(n);
    For(i, n) cin >> s[i];
    ranges::sort(s);

    int ans = (c + 1) * (c + 2) / 2;

    int sum1 = 0, sum = 0;
    int cnt0 = 0, cnt1 = 0, total = 0;
    for (int x: s) {
        sum1 += x / 2;
        sum += x;
        if (x & 1) {
            total += cnt1 + 1;
            ++cnt1;
        } else {
            total += cnt0 + 1;
            ++cnt0;
        }
    }

    ans -= (sum1 + n);
    ans -= n * (c + 1) - sum;
    ans += total;

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
