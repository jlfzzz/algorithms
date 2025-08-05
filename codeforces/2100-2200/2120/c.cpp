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

    for (int i = 1; i <= n; i++) {
        ll mx = (n - i + 1) * i + (1 + i - 1) * (i - 1) / 2;
        ll mn = i + n - 1;

        if (m >= mn and m <= mx) {
            ll curr = mx;
            vector<pll> ans;

            while (curr > m) {

            }
            break;
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
