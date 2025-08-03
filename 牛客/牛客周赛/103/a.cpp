#include <bits/stdc++.h>
#include <string>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;
    string s = to_string(n);
    reverse(s.begin(), s.end());
    if (s[0] == '0') {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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
