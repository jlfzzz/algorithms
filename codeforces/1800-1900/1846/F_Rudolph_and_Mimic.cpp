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
    cin >> n;

    vector<int> a(n + 1);
    vector<int> sum(10, 0);
    vector<int> cnt(10, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[a[i]]++;
    }

    cout << "- 0" << endl;

    while (1) {
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        for (k = 1; k <= 9; k++) {
            if (cnt[k] == sum[k] + 1)
                break;
        }
        if (k != 10)
            break;
        cout << "- 0" << endl;
    }

    cout << "-";
    int m = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] != k)
            m++;
    cout << ' ' << m;
    for (int i = 1; i <= n; i++)
        if (a[i] != k)
            cout << ' ' << i;
    cout << endl;


    n = n - m;

    while (1) {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++) {
            if (a[i] != k) {
                cout << "! " << i << endl;

                return;
            }
        }
        cout << "- 0" << endl;
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
