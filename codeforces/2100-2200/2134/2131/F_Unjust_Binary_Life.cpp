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
    string a, b;
    cin >> a;
    cin >> b;

    struct Info {
        int d, c0, c1;
    };

    vector<Info> pre_a(n + 1), pre_b(n + 1);
    For(i, n) {
        pre_a[i + 1] = pre_a[i];
        if (a[i] == '0') {
            pre_a[i + 1].c0++;
        } else {
            pre_a[i + 1].c1++;
        }
        pre_a[i + 1].d = pre_a[i + 1].c0 - pre_a[i + 1].c1;

        pre_b[i + 1] = pre_b[i];
        if (b[i] == '0') {
            pre_b[i + 1].c0++;
        } else {
            pre_b[i + 1].c1++;
        }
        pre_b[i + 1].d = pre_b[i + 1].c0 - pre_b[i + 1].c1;
    }

    sort(pre_b.begin() + 1, pre_b.end(), [&](Info &a, Info &b) { return a.d < b.d; });
    vector<int> pre1(n + 1), pre2(n + 1);
    For(i, n) {
        pre1[i + 1] = pre1[i] + pre_b[i + 1].c0;
        pre2[i + 1] = pre2[i] + pre_b[i + 1].c1;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        auto &[d, c0, c1] = pre_a[i];
        int L = -d;

        int R = upper_bound(pre_b.begin() + 1, pre_b.begin() + n + 1, L,
                            [](int value, const Info &info) { return value < info.d; }) -
                pre_b.begin();

        ans += c0 * (R - 1) + pre1[R - 1];
        if (R != n + 1) {
            ans += c1 * (n - R + 1) + pre2[n] - pre2[R - 1];
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
