#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    cout.flush();
    int n;
    cin >> n;
    int a = 1, b = 2, c = 3;
    while (1) {
        cout << '?' << ' ' << a << ' ' << b << ' ' << c << '\n';
        cout.flush();
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 2);
        int p = dist(rng);
        int x;
        cin >> x;
        if (x == 0) {
            cout << '!' << ' ' << a << ' ' << b << ' ' << c << '\n';
            return;
        }
        if (p == 0)
            a = x;
        else if (p == 1)
            b = x;
        else
            c = x;
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
