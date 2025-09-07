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
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> cnt(n + 3, 0);
    for (int x: a)
        cnt[x]++;

    int m = 0;
    while (m <= n && cnt[m] > 0)
        m++;

    int one = 0;
    int s1 = 0;
    for (int x = 0; x < m; x++)
        if (cnt[x] == 1) {
            one++;
            s1 += x;
        }

    int sb = s1 + m * (n - one);

    int m1 = m + 1; // 下一个
    for (int x = 0; x < m; x++)
        if (cnt[x] >= 2) {
            m1 = x;
            break;
        }

    int sc;
    if (m1 <= m - 1) {
        int one2 = 0, s2 = 0;
        for (int x = 0; x < m1; x++)
            if (cnt[x] == 1) {
                one2++;
                s2 += x;
            }
        sc = s2 + (n - one2) * m1;
    } else {
        int sm = m * (m - 1) / 2;
        int cm = n - m;
        if (cm == 1)
            sc = sm + m;
        else
            sc = sm + cm * (m + 1);
    }
    int sd;
    if (m1 <= m - 1) {
        int cm1 = n - m1;
        if (cm1 == 1)
            sd = sc;
        else
            sd = sc + cm1;
    } else {
        int cm = n - m;
        if (cm == 1)
            sd = sc;
        else
            sd = sc - cm;
    }

    if (k == 1)
        cout << sb << '\n';
    else if ((k & 1) == 0)
        cout << sc << '\n';
    else
        cout << sd << '\n';
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
