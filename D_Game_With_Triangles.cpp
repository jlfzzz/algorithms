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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int kmax = min({n, m, (n + m) / 3});
    if (kmax == 0) {
        cout << 0 << '\n';
        return;
    }

    int mA = n / 2;
    vector<int> preA(mA + 1, 0);
    for (int i = 1; i <= mA; i++) {
        preA[i] = preA[i - 1] + (a[n - i] - a[i - 1]);
    }

    int mB = m / 2;
    vector<int> preB(mB + 1, 0);
    for (int i = 1; i <= mB; i++) {
        preB[i] = preB[i - 1] + (b[m - i] - b[i - 1]);
    }

    vector<int> res;
    for (int k = 1; k <= kmax; k++) {
        int L = max(0ll, 2 * k - m);
        int R = min(k, n - k);
        if (L > R) {
            continue;
        }
        int low = L, high = R;
        while (high - low > 2) {
            int mid1 = low + (high - low) / 3;
            int mid2 = high - (high - low) / 3;
            int val1 = preA[mid1] + preB[k - mid1];
            int val2 = preA[mid2] + preB[k - mid2];
            if (val1 < val2) {
                low = mid1;
            } else {
                high = mid2;
            }
        }
        int best = 0;
        for (int i = low; i <= high; i++) {
            if (i <= mA && (k - i) <= mB) {
                best = max(best, preA[i] + preB[k - i]);
            }
        }
        res.push_back(best);
    }

    cout << kmax << '\n';
    for (int x: res) {
        cout << x << ' ';
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
