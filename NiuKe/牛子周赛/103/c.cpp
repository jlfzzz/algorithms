#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = int(1e9 + 7);
long long qpow(long long a, long long b, int mod) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    long long n;
    cin >> n;
    cout << qpow(2, n - 1, MOD) << '\n';
    return 0;
}
