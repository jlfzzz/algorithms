#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 每次调用 query min/max 前必须调用 rebuild
struct LB {
    using i64 = long long;
    const int BASE = 63;
    vector<i64> d, p;
    int cnt, flag;

    LB() {
        d.resize(BASE + 1);
        p.resize(BASE + 1);
        cnt = flag = 0;
    }

    void clear() {
        d.assign(BASE + 1, 0);
        p.assign(BASE + 1, 0);
        cnt = flag = 0;
    }

    bool insert(i64 val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    return true;
                }
                val ^= d[i];
            }
        }
        flag = 1;
        return false;
    }

    bool check(i64 val) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                val ^= d[i];
            }
        }
        return val == 0;
    }

    i64 ask_max() {
        i64 res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res)
                res ^= d[i];
        }
        return res;
    }

    i64 ask_min() {
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i])
                return d[i];
        }
        return 0;
    }

    void rebuild() {
        p.assign(BASE + 1, 0);
        cnt = 0;
        auto temp_d = d;

        for (int i = BASE - 1; i >= 0; i--) {
            if (temp_d[i]) {
                for (int j = i - 1; j >= 0; j--) {
                    if (temp_d[i] & (1ll << j))
                        temp_d[i] ^= temp_d[j];
                }
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (temp_d[i])
                p[cnt++] = temp_d[i];
        }
    }

    i64 ask_kth_min(i64 k) {
        i64 total_sums = (1LL << cnt);
        if (k <= 0 || k > total_sums)
            return -1;

        i64 k_loop = k - 1;

        i64 res = 0;
        for (int i = 0; i < cnt; i++) {
            if (k_loop & (1LL << i))
                res ^= p[i];
        }
        return res;
    }

    i64 ask_kth_max(i64 k) {
        i64 total_sums = (1LL << cnt);
        if (k <= 0 || k > total_sums)
            return -1;

        i64 k_loop = total_sums - k;

        i64 res = 0;
        for (int i = 0; i < cnt; i++) {
            if (k_loop & (1LL << i))
                res ^= p[i];
        }
        return res;
    }

    void Merge(const LB &b) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.d[i]) {
                insert(b.d[i]);
            }
        }
        flag = flag | b.flag;
        cnt = 0;
    }

    int get_rank() {
        int rank = 0;
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i] != 0) {
                rank++;
            }
        }
        return rank;
    }
};
