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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), b(m);
    For(i, n) cin >> a[i];
    For(i, m) cin >> b[i];

    ranges::sort(a, greater<>());
    ranges::sort(b, greater<>());

    vector<long long> preA(n + 1), preB(m + 1);
    for (int i = 1; i <= n; i++)
        preA[i] = preA[i - 1] + a[i - 1];
    for (int i = 1; i <= m; i++)
        preB[i] = preB[i - 1] + b[i - 1];

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;

        if (z == 0) {
            cout << 0 << "\n";
            continue;
        }

        auto f = [&](int takeA) -> long long {
            if (takeA < 0 || takeA > n)
                return LLONG_MIN / 4;
            int takeB = z - takeA;
            if (takeB < 0 || takeB > m)
                return LLONG_MIN / 4;
            return preA[takeA] + preB[takeB];
        };

        int L = max(0LL, z - y), R = min(z, x);

        while (L < R) {
            int mid = (L + R) / 2;
            long long v1 = f(mid), v2 = f(mid + 1);
            if (v1 <= v2) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        cout << f(L) << "\n";
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
