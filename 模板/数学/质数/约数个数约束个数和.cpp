#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 约数个数

namespace div_cnt {
    constexpr int N = 1'000'005;
    int p[N], vis[N], cnt;
    int a[N], d[N];

    void get_d(int n) {
        assert(n < N);
        d[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) {
                p[++cnt] = i;
                a[i] = 1;
                d[i] = 2;
            }
            for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
                int m = i * p[j];
                vis[m] = 1;
                if (i % p[j] == 0) {
                    a[m] = a[i] + 1;
                    d[m] = d[i] / a[m] * (a[m] + 1);
                    break;
                } else {
                    a[m] = 1;
                    d[m] = d[i] * 2;
                }
            }
        }
    }
}; // namespace div_cnt
