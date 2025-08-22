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
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    int B = sqrt(n) + 1;


    // 一维是d,二维是余数
    vector<vector<vector<int>>> pre1(B);
    vector<vector<vector<int>>> pre2(B);

    for (int i = 1; i < B; i++) {
        vector<vector<int>> v1(i);
        vector<vector<int>> v2(i);
        for (int j = 1; j < i; j++) {
            vector<int> t1(n / i + 5);
            vector<int> t2(n / i + 5);

            for (int k = 0; k * i + j <= n; k++) {
                t1[k + 1] = t1[k] + a[k * i + j];
                t2[k + 1] = t2[k] + (k + 1) * a[k * i + j];
            }
            v1[j] = std::move(t1);
            v2[j] = std::move(t2);
        }

        vector<int> t1(n / i + 5);
        vector<int> t2(n / i + 5);
        for (int k = 1; k * i <= n; k++) {
            t1[k] = t1[k - 1] + a[k * i];
            t2[k] = t2[k - 1] + k * a[k * i];
        }

        v1[0] = std::move(t1);
        v2[0] = std::move(t2);

        pre1[i] = std::move(v1);
        pre2[i] = std::move(v2);
    }

    For(_, q) {
        int s, d, k;
        cin >> s >> d >> k;

        int ans = 0;
        if (d >= B) {
            for (int i = 0; i < k; i++) {
                ans += a[s + i * d] * (i + 1);
            }
        } else {
            int rem = s % d;

            auto &v1 = pre1[d][rem];
            auto &v2 = pre2[d][rem];
            // cout << k << endl;

            int i = (s - rem) / d;
            if (rem != 0)
                i++;
            k = i + k - 1;
            // cout << i << endl;
            // cout << k << endl;
            // cout << v1[k] << endl;
            // cout << v2[k] << endl;
            int sum1 = v1[k] - v1[i - 1];
            int sum2 = v2[k] - v2[i - 1];

            ans = sum2 - (i - 1) * sum1;
        }
        cout << ans << ' ';
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
