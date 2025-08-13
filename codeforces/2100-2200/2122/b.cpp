#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    struct t {
        int a, b, c, d;
    };

    vector<t> arr(n);
    For(i, n) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        arr[i] = {a, b, c, d};
    }

    int ans = 0;
    For(i, n) {
        auto &temp = arr[i];
        int a = temp.a, b = temp.b, c = temp.c, d = temp.d;
        if (a <= c and b <= d) {
            continue;
        } else if (b > d) {
            ans += a + b - d;
        } else {
            ans += a - c;
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
