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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = string(" ") + s;

    set<int> ba, bc, cb, ca;
    for (int i = 1; i <= q; i++) {
        char x, y;
        cin >> x >> y;
        if (x == 'b') {
            if (y == 'a')
                ba.insert(i);
            else if (y == 'c')
                bc.insert(i);
        } else if (x == 'c') {
            if (y == 'a')
                ca.insert(i);
            else if (y == 'b')
                cb.insert(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (s[i] == 'b') {
            if (!ba.empty()) {
                s[i] = 'a';
                ba.erase(*ba.begin());
            } else if (!bc.empty() && !ca.empty()) {
                int BC = *bc.begin();
                auto CA = ca.upper_bound(BC);
                if (CA != ca.end()) {
                    s[i] = 'a';
                    bc.erase(BC);
                    ca.erase(*CA);
                }
            }
        } else if (s[i] == 'c') {
            if (!ca.empty()) {
                s[i] = 'a';
                ca.erase(*ca.begin());
            } else if (!cb.empty()) {
                if (!ba.empty()) {
                    int CB = *cb.begin();
                    auto BA = ba.upper_bound(CB);
                    if (BA == ba.end()) {
                        s[i] = 'b';
                        cb.erase(CB);
                    } else {
                        s[i] = 'a';
                        cb.erase(CB);
                        ba.erase(*BA);
                    }
                } else {
                    s[i] = 'b';
                    cb.erase(*cb.begin());
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << s[i];
    cout << '\n';
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
