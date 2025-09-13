#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cover = 0;
    int maxv = 0;
};

struct SegTree {
    int n;
    vector<Node> tr;

    SegTree(int n) : n(n), tr(4 * n) {}

    void push_up(int o) { tr[o].maxv = max(tr[o << 1].maxv, tr[o << 1 | 1].maxv) + tr[o].cover; }

    void update(int o, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            tr[o].cover += val;
            tr[o].maxv += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(o << 1, l, mid, ql, qr, val);
        if (qr > mid)
            update(o << 1 | 1, mid + 1, r, ql, qr, val);
        push_up(o);
    }

    int query_max() { return tr[1].maxv; }
};

struct Interval {
    int l, r, len;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Interval> segs(n);
    vector<int> coords;

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        segs[i] = {l, r, r - l};
        coords.push_back(l);
        coords.push_back(r);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto getid = [&](int x) {
        return int(lower_bound(coords.begin(), coords.end(), x) - coords.begin()) + 1;
    };

    for (auto &s: segs) {
        s.l = getid(s.l);
        s.r = getid(s.r);
    }

    sort(segs.begin(), segs.end(), [](auto &a, auto &b) { return a.len < b.len; });

    int N = coords.size();
    SegTree st(N);

    int ans = INT_MAX;
    int L = 0;
    for (int R = 0; R < n; R++) {
        st.update(1, 1, N, segs[R].l, segs[R].r, 1);

        while (L <= R && st.query_max() >= m) {
            ans = min(ans, segs[R].len - segs[L].len);
            st.update(1, 1, N, segs[L].l, segs[L].r, -1);
            L++;
        }
    }

    if (ans == INT_MAX)
        cout << -1 << "\n";
    else
        cout << ans << "\n";

    return 0;
}
