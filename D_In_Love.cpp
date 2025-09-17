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
    int q;
    cin >> q;
    multiset<ll> L, R;
    map<pair<ll, ll>, int> cnt;

    while (q--) {
        char op;
        ll l, r;
        cin >> op >> l >> r;
        if (op == '+') {
            cnt[{l, r}]++;
            L.insert(l);
            R.insert(r);
        } else {
            auto itcnt = cnt.find({l, r});
            if (itcnt != cnt.end()) {
                if (--itcnt->second == 0)
                    cnt.erase(itcnt);
            }
            auto itL = L.find(l);
            if (itL != L.end())
                L.erase(itL);
            auto itR = R.find(r);
            if (itR != R.end())
                R.erase(itR);
        }

        if (L.size() < 2) {
            cout << "NO\n";
        } else {
            ll maxL = *prev(L.end());
            ll minR = *R.begin();
            cout << (maxL > minR ? "YES\n" : "NO\n");
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
