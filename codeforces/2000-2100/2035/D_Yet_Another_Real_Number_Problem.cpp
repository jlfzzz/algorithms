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

    auto q_pow = [&](int b, int e) {
        int res = 1;
        while (e) {
            if (e & 1) {
                res = res * b % MOD;
            }
            b = b * b % MOD;
            e /= 2;
        }
        return res;
    };

    vector<pii> stk;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        int cnt2 = 0;
        while ((x & 1) == 0) {
            cnt2++;
            x >>= 1;
        }
        a[i] = x;

        auto ge2 = [&](int xv, int e, int yv) {
            if (e >= 31)
                return true;
            return ((i128) xv << e) >= (i128) yv;
        };

        while (!stk.empty()) {
            auto [j, p2] = stk.back();
            if (ge2(a[i], cnt2, a[j])) {
                stk.pop_back();
                cnt2 += p2;
                sum = (sum - (a[j] * q_pow(2, p2) % MOD) + MOD) % MOD;
                sum = (sum + a[j]) % MOD;
            } else
                break;
        }
        stk.emplace_back(i, cnt2);
        sum = (sum + a[i] * q_pow(2, cnt2) % MOD) % MOD;
        cout << sum << ' ';
    }
    cout << '\n';
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
