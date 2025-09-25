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
    int n;
    cin >> n;
    string s;
    cin >> s;

    set<int> a, b;
    For(i, n) {
        if (s[i] == 'A') {
            a.insert(i + 1);
        } else {
            b.insert(i + 1);
        }
    }

    auto f1 = []() { cout << "Alice\n"; };

    auto f2 = []() { cout << "Bob\n"; };
    if (a.contains(1) && a.contains(n)) {
        f1();
    } else if (a.contains(1)) {
        if (b.contains(n) && b.size() == 1) {
            f1();
        } else {
            f2();
        }
    } else if (b.contains(1) && a.contains(n) && a.contains(n - 1)) {
        f1();
    } else {
        f2();
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
