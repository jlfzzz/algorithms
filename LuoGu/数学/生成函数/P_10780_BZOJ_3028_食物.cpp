#include <bits/stdc++.h>
using namespace std;
long long n;
const int MOD = 10007;
int qpow(int x, int y) {
    int k = x;
    int res = 1;
    while (y) {
        if (y & 1)
            res = res * k % MOD;
        k = k * k % MOD;
        y >>= 1;
    }
    return res % MOD;
}
int main() {
    char c;
    c = getchar();
    while (c >= '0' && c <= '9') {
        n = (n * 10 + (c - '0')) % MOD;
        c = getchar();
    }
    printf("%lld", ((n + 2) * (n + 1) * n) * qpow(6, 10005) % MOD);
}
