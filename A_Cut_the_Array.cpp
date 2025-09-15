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

    auto prt = [&](int a, int b) { cout << a << ' ' << b << '\n'; };

    for (int i = 1; i <= n - 2; i++) {
        int s1 = 0;
        for (int j = 1; j <= i; j++) {
            s1 += a[j];
            s1 %= 3;
        }
        int s2 = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            s2 += a[j];
            s2 %= 3;
            if (s2 == s1) {
                int s3 = 0;
                for (int k = j + 1; k <= n; k++) {
                    s3 += a[k];
                }
                s3 %= 3;
                if (s3 == s2) {
                    prt(i, j);
                    return;
                }
            }
        }
    }

    for (int i = 1; i <= n - 2; i++) {
        int s1 = 0;
        for (int j = 1; j <= i; j++) {
            s1 += a[j];
        }
        s1 %= 3;
        int s2 = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            s2 += a[j];
            s2 %= 3;
            if (s2 != s1) {
                int s3 = 0;
                for (int k = j + 1; k <= n; k++) {
                    s3 += a[k];
                }
                s3 %= 3;
                if (s3 != s2 && s3 != s1) {
                    prt(i, j);
                    return;
                }
            } else {
                continue;
            }
        }
    }

    prt(0, 0);
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
