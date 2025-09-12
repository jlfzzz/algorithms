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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> p(n);
    int l = 1, r = n;

    vector<int> b(n);
    iota(b.begin(), b.end(), 0);

    for (int t = 1; b.size() > 1; t++) {
        int x = 0;
        while (x < b.size() && a[b[x]] == t) {
            x++;
        }

        for (int i = 0; i < x; i++) {
            if (a[b[i]] == t) {
                p[b[i]] = t % 2 == 1 ? r-- : l++;
            }
        }
        for (int i = b.size() - 1; i > x; i--) {
            if (a[b[i]] == t) {
                p[b[i]] = t % 2 == 1 ? r-- : l++;
            }
        }

        vector<int> nb;
        for (auto i: b) {
            if (a[i] != t) {
                nb.push_back(i);
            }
        }
        b = move(nb);
    }

    p[b[0]] = l;
    for (int i = 0; i < n; i++) {
        cout << p[i] << " \n"[i == n - 1];
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
