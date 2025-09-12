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
    string s;
    cin >> s;
    int pos;
    cin >> pos;

    int m = (int) s.size();

    auto f = [&](int k) -> int { return m * k - (k - 1) * k / 2; };

    int l = 1, r = m, k = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (f(mid) >= pos) {
            k = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    int pre = f(k - 1);
    int j = pos - pre;

    int d = k - 1;
    string res;
    for (char c: s) {
        while (d && !res.empty() && res.back() > c) {
            res.pop_back();
            d--;
        }
        res.push_back(c);
    }
    if (d)
        res.resize(res.size() - d);

    cout << res[j - 1];
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
