#include <bits/stdc++.h>
#include <vector>
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
    ll n, m;
    cin >> n >> m;

    if ((1 + n) * n / 2 < m or m < n) {
        cout << -1 << '\n';
        return;
    }

    vector<ll> fa(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll mx = (n - i + 1) * i + (1 + i - 1) * (i - 1) / 2;
        ll mn = i + n - 1;

        if (m >= mn and m <= mx) {
            ll curr = mx;
            for (ll j = 1; j <= n; j++) {
                fa[j] = i;
            }

            for (ll j = n; j >= 1; j--) {
                if (curr == m) {
                    break;
                }
                assert(m < curr);
                if (j != i and m < curr) {
                    if (curr - m >= i - 1) {
                        fa[j] = 1;
                        curr -= i - 1;
                    } else {
                        ll x = m - curr + i;
                        fa[j] = x;
                        curr -= i - x;
                    }
                }
            }

            cout << i << '\n';
            for (ll j = 1; j <= n; j++) {
                if (j != i) {
                    cout << fa[j] << ' ' << j << '\n';
                }
            }

            return;
        }
    }
    cout << -1 << '\n';
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
