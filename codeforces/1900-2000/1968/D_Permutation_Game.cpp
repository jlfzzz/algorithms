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
    int n, k, p1, p2;
    cin >> n >> k >> p1 >> p2;
    vector<int> p(n + 1), a(n + 1);
    For(i, n) cin >> p[i + 1];
    For(i, n) cin >> a[i + 1];

    auto f = [&](int start) -> int {
        int res = -inf;
        int pre = 0, t = k;
        For(i, n) {
            if (t < 0) {
                break;
            }
            int nxt = p[start], val = a[start];
            res = max(res, pre + t * val);
            start = nxt, pre += val, t -= 1;
        }
        return res;
    };

    int ans1 = f(p1), ans2 = f(p2);
    if (ans1 > ans2) {
        cout << "Bodya\n";
    } else if (ans1 < ans2) {
        cout << "Sasha\n";
    } else {
        cout << "Draw\n";
    }
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
