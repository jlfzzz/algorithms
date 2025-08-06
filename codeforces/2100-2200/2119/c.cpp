#include <bit>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    ll n, l, r, k;
    cin >> n >> l >> r >> k;

    if (n & 1) {
        cout << l << '\n';
    } else {
        if (n == 2) {
            cout << -1 << '\n';
            return;
        }
        ll x = bit_width((unsigned long long) l);
        ll t = 1ll << x;
        if (t > r) {
            cout << -1 << '\n';
        } else {
            if (k == n or k == n - 1) {
                cout << t << '\n';
            } else {
                cout << l << '\n';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
