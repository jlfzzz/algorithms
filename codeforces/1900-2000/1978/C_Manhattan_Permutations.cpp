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
    vector<int> a(n + 1);
    if (k % 2 == 1)
        cout << "No" << '\n';
    else {
        int ans = 0;
        for (int i = 1, j = n; i <= n; i++, j--) {
            a[i] = i;
            ans += abs(j - i);
        }
        if (k > ans)
            cout << "No" << '\n';
        else {
            int x = k / 2;
            int i = 1, j = n;
            while (i < j) {
                int contri = abs(i - j);
                if (x >= contri) {
                    x -= contri;
                    swap(a[i], a[j]);
                    j--;
                }
                i++;
            }
            // for (int i = 1, j = min(x, n - 1);; i++) {
            //     swap(a[i], a[i + j]);
            //     x -= j;
            //     j = min(x, n - 2 * i - 1);
            //     if (!x)
            //         break;
            // }
            cout << "Yes" << '\n';
            for (int i = 1; i <= n; i++)
                cout << a[i] << " ";
            cout << '\n';
        }
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
