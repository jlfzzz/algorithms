#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)

void init() {}

void solve() {
    int n, m;
    if (!(cin >> n >> m))
        return;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    sort(a.begin(), a.end());
    vector<pair<int, int>> ar;
    for (int i = 0; i < n;) {
        int j = i;
        while (j + 1 < n && a[j + 1] == a[j] + 1)
            j++;
        ar.push_back({a[i], a[j]});
        i = j + 1;
    }
    struct Seg {
        int t;
        int l;
        int r;
    };
    vector<Seg> seg;
    int N = n + m;
    int prev = 0;
    for (auto [L, R]: ar) {
        if (prev + 1 <= L - 1)
            seg.push_back({1, prev + 1, L - 1});
        seg.push_back({0, L, R});
        prev = R;
    }
    if (prev < N)
        seg.push_back({1, prev + 1, N});
    auto out = [&](int a1, int a2, int b1, int b2) { cout << a1 << ' ' << a2 << ' ' << b1 << ' ' << b2 << '\n'; };
    auto fail = [&]() { cout << -1 << '\n'; };
    auto len = [&](const Seg &s) { return s.r - s.l + 1; };
    int S = seg.size();
    if (S <= 2) {
        fail();
        return;
    }
    if (S == 3) {
        auto s0 = seg[0], s1 = seg[1], s2 = seg[2];
        if (s1.t == 1) {
            if (len(s1) < 2) {
                fail();
                return;
            }
            out(s0.r, s2.l, s1.l, s1.r);
        } else {
            if (len(s1) < 2) {
                fail();
                return;
            }
            out(s1.l, s1.r, s0.r, s2.l);
        }
        return;
    }
    if (S == 4) {
        auto s0 = seg[0], s1 = seg[1], s2 = seg[2], s3 = seg[3];
        if (len(s1) >= 2) {
            if (s1.t == 1)
                out(s0.r, s2.l, s1.l, s1.r);
            else
                out(s1.l, s1.r, s0.r, s2.l);
            return;
        }
        if (len(s2) >= 2) {
            if (s2.t == 1)
                out(s1.r, s3.l, s2.l, s2.r);
            else
                out(s2.l, s2.r, s1.r, s3.l);
            return;
        }
        fail();
        return;
    }
    {
        auto s0 = seg[0], s1 = seg[1], s3 = seg[3], s4 = seg[4];
        if (s0.t == 0)
            out(s0.r, s4.l, s1.l, s3.r);
        else
            out(s1.l, s3.r, s0.r, s4.l);
        return;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
