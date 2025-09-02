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

    vector<int> A1(n + 1), B1(n + 1), A0(n + 1), B0(n + 1);
    For(i, n) {
        A1[i + 1] = A1[i] + (a[i] == '1');
        B1[i + 1] = B1[i] + (b[i] == '1');
        A0[i + 1] = (i + 1) - A1[i + 1];
        B0[i + 1] = (i + 1) - B1[i + 1];
    }

    struct Info {
        int d, c0, c1;
    };
    vector<Info> vb(n + 1);
    for (int y = 1; y <= n; y++)
        vb[y] = Info{2 * (int) B1[y] - y, B0[y], B1[y]};
    sort(vb.begin() + 1, vb.end(), [&](const Info &x, const Info &y) { return x.d < y.d; });

    vector<int> pre0(n + 1), pre1(n + 1);
    for (int i = 1; i <= n; i++) {
        pre0[i] = pre0[i - 1] + vb[i].c0;
        pre1[i] = pre1[i - 1] + vb[i].c1;
    }

    long long ans = 0;
    for (int x = 1; x <= n; x++) {
        int C = A1[x];
        int D = A0[x];
        int T = D - C;
        int pos = upper_bound(vb.begin() + 1, vb.begin() + n + 1, T, [](int v, const Info &t) { return v < t.d; }) -
                  vb.begin() - 1; // d <= T
        if (pos < 0)
            pos = 0;
        int cntL = pos;
        int cntR = n - cntL;
        long long sumB1_L = pre1[cntL];
        long long sumB0_R = pre0[n] - pre0[cntL];

        ans += (long long) C * cntL + sumB1_L;
        ans += (long long) D * cntR + sumB0_R;
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
