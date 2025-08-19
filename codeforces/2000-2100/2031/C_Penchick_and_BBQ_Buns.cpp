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
const int sub[] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 1, 6};
void solve() {
    int n;
    cin >> n;
    if (n % 2 == 0) {
        for (int i = 1; i <= n / 2; i++)
            cout << i << ' ' << i << ' ';
        cout << endl;
    } else {
        if (n < 27)
            cout << -1 << endl;
        else {
            for (int i: sub)
                cout << i << ' ';
            n -= 27;
            for (int i = 14; i <= 13 + n / 2; i++)
                cout << i << ' ' << i << ' ';
            cout << endl;
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
