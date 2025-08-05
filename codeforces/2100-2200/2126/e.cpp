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
    vector<int> p(n);
    vector<int> s(n);
    For(i, n) cin >> p[i];
    For(i, n) cin >> s[i];

    if (s[0] != p[n - 1]) {
        cout << "No\n";
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        if (p[i] % p[i + 1] || s[i + 1] % s[i]) {
            cout << "No\n";
            return;
        }
        if (gcd(p[i], s[i + 1]) != p[n - 1]) {
            cout << "No\n";
            return;
        }
    }
    cout << "YES\n";
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
