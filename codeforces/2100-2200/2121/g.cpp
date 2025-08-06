#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5 + 5;
int t, n;
string s;
vector<int> pref;

struct BIT {
    vector<ll> tree;
    int size;

    BIT(int n) {
        size = n + 2;
        tree.assign(size, 0);
    }

    void add(int i, ll x) {
        for (++i; i < size; i += i & -i)
            tree[i] += x;
    }

    ll query(int i) {
        ll res = 0;
        for (++i; i > 0; i -= i & -i)
            res += tree[i];
        return res;
    }

    ll query(int l, int r) { return query(r) - query(l - 1); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> s;
        pref.resize(n + 1);
        pref[0] = 0;
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : -1);
        }

        // 离散化
        vector<int> all = pref;
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());

        auto get_id = [&](int x) { return lower_bound(all.begin(), all.end(), x) - all.begin(); };

        int m = all.size();
        BIT cnt_bit(m), sum_bit(m);

        ll ans = 0;

        // 加入 pref[0]
        cnt_bit.add(get_id(pref[0]), 1);
        sum_bit.add(get_id(pref[0]), pref[0]);

        for (int i = 1; i <= n; i++) {
            int id = get_id(pref[i]);

            // 统计左边 < 当前值的部分
            ll cnt_left = cnt_bit.query(id - 1);
            ll sum_left = sum_bit.query(id - 1);
            // 右边 > 当前值的部分
            ll cnt_total = cnt_bit.query(m - 1);
            ll sum_total = sum_bit.query(m - 1);
            ll cnt_right = cnt_total - cnt_bit.query(id);
            ll sum_right = sum_total - sum_bit.query(id);

            ll v = pref[i];
            ll contrib = (v * cnt_left - sum_left) + (sum_right - v * cnt_right);
            ans += contrib;

            // 插入当前值
            cnt_bit.add(id, 1);
            sum_bit.add(id, v);
        }

        // 加上所有子串长度总和
        for (int len = 1; len <= n; len++) {
            ans += 1LL * len * (n - len + 1);
        }

        cout << ans / 2 << '\n';
    }
    return 0;
}
