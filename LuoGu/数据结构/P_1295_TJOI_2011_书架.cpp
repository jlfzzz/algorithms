#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll) 4e18;

struct SegTree {
    int n;
    vector<ll> seg, lazy;
    SegTree(int n) : n(n) {
        seg.assign(4 * n + 4, INF);
        lazy.assign(4 * n + 4, 0);
    }
    void apply(int p, ll v) {
        seg[p] += v;
        lazy[p] += v;
    }
    void push(int p) {
        if (!lazy[p])
            return;
        apply(p << 1, lazy[p]);
        apply(p << 1 | 1, lazy[p]);
        lazy[p] = 0;
    }
    void add(int p, int l, int r, int ql, int qr, ll v) {
        if (ql > r || qr < l)
            return;
        if (ql <= l && r <= qr) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        add(p << 1, l, m, ql, qr, v);
        add(p << 1 | 1, m + 1, r, ql, qr, v);
        seg[p] = min(seg[p << 1], seg[p << 1 | 1]);
    }
    void add(int l, int r, ll v) {
        if (l > r)
            return;
        add(1, 1, n, l, r, v);
    }
    ll getMin(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return INF;
        if (ql <= l && r <= qr)
            return seg[p];
        push(p);
        int m = (l + r) >> 1;
        return min(getMin(p << 1, l, m, ql, qr), getMin(p << 1 | 1, m + 1, r, ql, qr));
    }
    ll getMin(int l, int r) {
        if (l > r)
            return INF;
        return getMin(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll m;
    if (!(cin >> n >> m))
        return 0;
    vector<ll> h(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> h[i];

    SegTree st(n);
    vector<ll> dp(n + 1);
    ll sum = 0;
    int L = 1, curL = 1;
    vector<pair<int, ll>> stk;
    stk.reserve(n);

    for (int i = 1; i <= n; i++) {
        sum += h[i];
        while (sum > m) {
            sum -= h[L];
            ++L;
        }

        int last_pos = i;
        ll hi = h[i];
        while (!stk.empty() && stk.back().second <= hi) {
            auto [start, height] = stk.back();
            stk.pop_back();
            if (start <= last_pos - 1)
                st.add(start, last_pos - 1, hi - height);
            last_pos = start;
        }
        stk.emplace_back(last_pos, hi);

        // val[i] = dp[i-1] + h[i]
        st.add(i, i, dp[i - 1] + h[i] - INF);

        while (curL < L) {
            st.add(curL, curL, INF);
            ++curL;
        }

        dp[i] = st.getMin(L, i);
    }

    cout << dp[n] << '\n';
    return 0;
}
