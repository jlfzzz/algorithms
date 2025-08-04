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
    int n;
    cin >> n;
    vector<ll> b(n);
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    ll x = 1;
    for (int i = 0; i < n - 1; ++i) {
        ll g = gcd(b[i], b[i + 1]);
        ll ratio = b[i] / g;
        x = lcm(x, ratio);
    }
    cout << x << '\n';
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
