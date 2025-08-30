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
    vector<int> A(6);
    for (int i = 0; i < 6; i++) {
        cin >> A[i];
    }
    ranges::sort(A);
    ranges::reverse(A);

    double ans = 0.0;
    for (int r1 = 0; r1 <= 6; r1++) {
        for (int r2 = 0; r2 <= 6 - r1; r2++) {
            int r3 = 6 - r1 - r2;
            if (r3 <= 0)
                continue;
            double round1 = 0.0;
            for (int i = 0; i < r1; i++) {
                round1 += A[i];
            }
            if (r1 > 0) {
                round1 /= r1;
            }
            double round2 = 0.0;
            for (int i = r1; i < r1 + r2; i++) {
                round2 += A[i];
            }
            if (r2 > 0) {
                round2 /= r2;
            }
            double round3 = 0.0;
            for (int i = r1 + r2; i < 6; i++) {
                round3 += A[i];
            }
            if (r3 > 0) {
                round3 /= r3;
            }

            double total = round1 + round2 + round3;
            if (total > ans) {
                ans = total;
            }
        }
    }

    cout << fixed << setprecision(10) << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
