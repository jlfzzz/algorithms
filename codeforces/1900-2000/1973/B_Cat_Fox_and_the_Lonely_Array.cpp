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
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    const int K = 22;
    auto check = [&](int k) -> bool {
        if (k == 0)
            return false;
        vector<int> cnt(K);
        auto add = [&](int x, int d) {
            for (int b = 0; b < K; b += 1)
                if (x >> b & 1)
                    cnt[b] += d;
        };
        for (int i = 1; i <= k; i += 1)
            add(a[i], 1);
        auto get = [&]() -> int {
            int v = 0;
            for (int b = 0; b < K; b += 1)
                if (cnt[b] > 0)
                    v |= (1ll << b);
            return v;
        };
        int target = get();
        for (int r = k + 1; r <= n; r += 1) {
            add(a[r - k], -1);
            add(a[r], 1);
            if (get() != target)
                return false;
        }
        return true;
    };
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
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
