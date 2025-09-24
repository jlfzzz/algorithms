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

struct Seg {
    int l, r;
    bool operator<(const Seg &other) const { return l < other.l; }
};


void solve() {
    int n;
    cin >> n;

    vector<Seg> v(n);
    For(i, n) {
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        v[i] = {l, b};
    }

    sort(v.begin(), v.end());
    set<Seg> st;
    for (int i = 0; i < n; i++) {
        auto [l, r] = v[i];
        while (i + 1 < n && v[i + 1].l >= l && v[i + 1].l <= r) {
            i++;
            r = max(r, v[i].r);
        }

        st.insert({l, r});
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;

        auto it = st.upper_bound({x, x});
        if (it != st.begin()) {
            it--;
            if (x <= it->r)
                x = it->r;
        }
        cout << x << ' ';
    }
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
