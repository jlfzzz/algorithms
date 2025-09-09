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

    struct Info {
        int l, r, id;
    };

    map<int, vector<pii>> cnt;
    For(i, n) {
        int l, r;
        cin >> l >> r;
        cnt[l].emplace_back(r, i);
    }

    vector<Info> v1, v2;
    for (auto &[l, vr]: cnt) {
        for (auto &[r, id]: vr) {
            v1.emplace_back(l, r, id);
            v2.emplace_back(l, r, id);
        }
    }

    ranges::sort(v1, [](Info &a, Info &b) { return a.l < b.l; });
    ranges::sort(v2, [](Info &a, Info &b) { return a.r > b.r; });

    int m = v1.size();
    vector<int> use(n);

    int ans = 0;
    int p1 = 0, p2 = 0;
    while (p1 < m && p2 < m) {
        auto &[l1, r1, id1] = v1[p1];
        if (use[id1]) {
            p1++;
            continue;
        }
        auto &[l2, r2, id2] = v2[p2];
        if (use[id2]) {
            p2++;
            continue;
        }

        if (id1 != id2) {
            ans += (r1 - l1) + (r2 - l2) + max(0ll, r2 - l1);
            use[id1] = use[id2] = 1;
            p1++, p2++;
            continue;
        }

        int i2 = p1 + 1;
        while (i2 < m && (use[v1[i2].id] || v1[i2].id == id2))
            i2++;
        int j2 = p2 + 1;
        while (j2 < m && (use[v2[j2].id] || v2[j2].id == id1))
            j2++;

        bool f1 = (j2 < m);
        bool f2 = (i2 < m);
        if (!f1 && !f2)
            break;

        if (f1 && !f2) {
            auto &[lA, rA, idA] = v2[j2];
            ans += (r1 - l1) + (rA - lA) + max(0ll, rA - l1);
            use[id1] = use[idA] = 1;
            p1++;
            continue;
        }
        if (!f1 && f2) {
            auto &[lB, rB, idB] = v1[i2];
            ans += (rB - lB) + (r2 - l2) + max(0ll, r2 - lB);
            use[idB] = use[id2] = 1;
            p2++;
            continue;
        }

        auto &[lA, rA, idA] = v2[j2];
        int c1 = max(0ll, rA - l1);
        auto &[lB, rB, idB] = v1[i2];
        int c2 = max(0ll, r2 - lB);
        if (c1 > c2) {
            ans += (r1 - l1) + (rA - lA) + c1;
            use[id1] = use[idA] = 1;
            p1++;
            continue;
        } else if (c2 > c1) {
            ans += (rB - lB) + (r2 - l2) + c2;
            use[idB] = use[id2] = 1;
            p2++;
            continue;
        } else {
            int i3 = i2;
            while (i3 < m && (use[v1[i3].id] || v1[i3].id == id1 || v1[i3].id == idA))
                i3++;
            int j3 = j2 + 1;
            while (j3 < m && (use[v2[j3].id] || v2[j3].id == id1 || v2[j3].id == idA))
                j3++;
            int C1 = 0;
            if (i3 < m && j3 < m)
                C1 = max(0ll, v2[j3].r - v1[i3].l);

            int i4 = i2 + 1;
            while (i4 < m && (use[v1[i4].id] || v1[i4].id == id2 || v1[i4].id == idB))
                i4++;
            int j4 = p2 + 1;
            while (j4 < m && (use[v2[j4].id] || v2[j4].id == id2 || v2[j4].id == idB))
                j4++;
            int C2 = 0;
            if (i4 < m && j4 < m)
                C2 = max(0ll, v2[j4].r - v1[i4].l);

            if (C1 >= C2) {
                ans += (r1 - l1) + (rA - lA) + c1;
                use[id1] = use[idA] = 1;
                p1++;
                continue;
            } else {
                ans += (rB - lB) + (r2 - l2) + c2;
                use[idB] = use[id2] = 1;
                p2++;
                continue;
            }
        }
    }

    // while (p1 < m) {
    //     auto &[l1, r1, id1] = v1[p1];
    //     if (use[id1]) {
    //         p1++;
    //         continue;
    //     }
    //     ans += r1 - l1;
    //     use[id1] = 1;
    //     p1++;
    // }

    // while (p2 < m) {
    //     auto &[l2, r2, id2] = v2[p2];
    //     if (use[id2]) {
    //         p2++;
    //         continue;
    //     }
    //     ans += r2 - l2;
    //     use[id2] = 1;
    //     p2++;
    // }
    for (int i = 0; i < m; i++) {
        if (!use[v1[i].id]) {
            ans += v1[i].r - v1[i].l;
        }
    }
    cout << ans << '\n';
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
