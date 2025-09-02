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

struct Segment {
    int l, r, id;
};

void solve() {
    int n;
    cin >> n;
    vector<Segment> v(n);
    For(i, n) {
        int l, r;
        cin >> l >> r;
        v[i] = {l, r, i};
    }

    ranges::sort(v, [](const Segment &a, const Segment &b) {
        if (a.l != b.l)
            return a.l < b.l;
        return a.r < b.r;
    });

    int R = v[0].r;
    vector<pii> ans;
    ans.emplace_back(v[0].id, 1);
    bool f = false;
    for (int i = 1; i < n; i++) {
        auto &[l, r, id] = v[i];
        if (f) {
            ans.emplace_back(id, 2);
            continue;
        }
        if (l > R) {
            f = true;
            ans.emplace_back(id, 2);
        } else {
            R = max(R, r);
            ans.emplace_back(id, 1);
        }
    }

    if (!f) {
        cout << -1 << '\n';
        return;
    }

    ranges::sort(ans);
    for (auto &[id, op]: ans) {
        cout << op << ' ';
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
