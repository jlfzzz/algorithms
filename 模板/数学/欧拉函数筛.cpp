#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 1'000'005;
int p[N], vis[N], cnt;
int phi[N];

void get_phi(int n) {
    assert(n < N);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            p[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < cnt && i * p[j] <= n; j++) {
            int m = i * p[j];
            vis[m] = 1;
            if (i % p[j] == 0) {
                phi[m] = p[j] * phi[i];
                break;
            } else {
                phi[m] = (p[j] - 1) * phi[i];
            }
        }
    }
}
