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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    auto f = [&](vector<int> &v) -> bool {
        int g = gcd(v[0], v[1]);
        for (int i = 1; i < v.size() - 1; i++) {
            int gg = gcd(v[i], v[i + 1]);
            if (gg < g) {
                return false;
            }
            g = gg;
        }
        return true;
    };

    int g = gcd(a[0], a[1]);
    int pos = -1;
    for (int i = 1; i < n - 1; i++) {
        int gg = gcd(a[i], a[i + 1]);
        if (gg < g) {
            pos = i;
            break;
        }
        g = gg;
    }

    if (pos == -1) {
        cout << "YES\n";
        return;
    }

    auto b = a;
    auto c = a;
    auto d = a;
    bool ans = false;
    b.erase(b.begin() + pos);
    ans |= f(b);
    if (pos - 1 >= 0) {
        c.erase(c.begin() + pos - 1);
        ans |= f(c);
    }

    if (pos + 1 < n) {
        d.erase(d.begin() + pos + 1);
        ans |= f(d);
    }

    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
