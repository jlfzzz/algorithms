#include "bits/stdc++.h"
using namespace std;
using ll = long long;

using Z = ll;

Z q_pow(Z base, long long exp) {
    Z result(1);
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}


// 光速幂
// 高位低位分别处理
const int B = 65536;
constexpr int P = 998244353;
int pow_lo[B];
int pow_hi[B];

void init() {}

void init_fast_pow(int x) {
    pow_lo[0] = 1;
    for (int i = 1; i < B; i++) {
        pow_lo[i] = 1LL * pow_lo[i - 1] * x % P;
    }

    int step = 1LL * pow_lo[B - 1] * x % P;

    pow_hi[0] = 1;
    for (int i = 1; i < B; i++) {
        pow_hi[i] = 1LL * pow_hi[i - 1] * step % P;
    }
}

void solve() {
    int x, n;
    cin >> x >> n;

    init_fast_pow(x);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int ans = 1LL * pow_hi[a >> 16] * pow_lo[a & 65535] % P;

        cout << ans << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}
