#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXV = 100005;
const int V = 350;

int a[MAXV];
int cnt[MAXV];
int blk_cnt[V];
int bel[MAXV];
int VB;

// 1-index
void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i];


    VB = sqrt(MAXV);
    for (int i = 0; i < MAXV; i++) {
        bel[i] = i / VB;
    }

    const int B = int(n / sqrt(q * 2.0 / 3.0 + 1)) + 1;

    struct Q {
        int l, r, k, id;
    };

    vector<Q> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), [&](Q &a, Q &b) {
        int l1 = a.l / B;
        int l2 = b.l / B;
        if (l1 != l2)
            return l1 < l2;
        return (l1 & 1) ? (a.r < b.r) : (a.r > b.r);
    });

    auto add = [&](int pos) {
        int val = a[pos];
        cnt[val]++;
        blk_cnt[bel[val]]++;
    };

    auto del = [&](int pos) {
        int val = a[pos];
        cnt[val]--;
        blk_cnt[bel[val]]--;
    };

    auto query_kth = [&](int k) -> int {
        int b = 0;
        while (b * VB < MAXV && k > blk_cnt[b]) {
            k -= blk_cnt[b];
            b++;
        }

        int start_val = b * VB;
        int end_val = min((b + 1) * VB - 1, MAXV - 1);

        for (int v = start_val; v <= end_val; ++v) {
            if (cnt[v] >= k)
                return v;
            k -= cnt[v];
        }
        return -1;
    };

    int L = 1, R = 0;
    vector<int> ans(q);

    for (auto &qry: queries) {
        while (L > qry.l)
            add(--L);
        while (R < qry.r)
            add(++R);
        while (L < qry.l)
            del(L++);
        while (R > qry.r)
            del(R--);

        ans[qry.id] = query_kth(qry.k);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
