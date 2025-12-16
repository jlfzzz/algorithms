#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;

    const int B = int(n / sqrt(q * 2 / 3 + 1)) + 1;

    struct Q {
        int l, r, id;
    };

    vector<Q> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), [&](Q &a, Q &b) {
        int l1 = a.l / B;
        int l2 = b.l / B;
        if (l1 != l2)
            return a.l < b.l;
        return (l1 & 1) ? (a.r < b.r) : (a.r > b.r);
    });

    auto add = [&](int pos) {

    };

    auto del = [&](int pos) {

    };

    int L = 1, R = 0;
    vector<ll> ans(q);
    for (auto &[l, r, id]: queries) {
        while (L > l)
            add(--L);
        while (R < r)
            add(++R);
        while (L < l)
            del(L++);
        while (R > r)
            del(R--);

        ans[id] = 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
