#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k, x;
    if (!(cin >> k >> x))
        return 0;
    long long n = 2 * k; // deck size
    long long p = x - 1; // 0-based position

    // Choose t so that 2^t >= n
    int t = 0;
    while ((1LL << t) < n)
        ++t;

    // Compute S such that after t steps: p_t = 2^t * p + S ≡ 0 (mod n)
    // => S ≡ - 2^t * p (mod n). Pick S in [0, n-1]
    long long pow2t_mod_n = ((1LL << t) % n);
    long long S = (n - (pow2t_mod_n * (p % n)) % n) % n;

    string ops;
    ops.reserve(t);
    for (int j = t - 1; j >= 0; --j) {
        int s = (int) ((S >> j) & 1LL); // current control bit (MSB first)
        bool inRight = (p >= k);
        // If s==0: choose op that makes c = (b xor h) = 0
        // Mapping to letters: left half -> s?R:L ; right half -> s?L:R
        char op;
        if (!inRight)
            op = (s ? 'R' : 'L');
        else
            op = (s ? 'L' : 'R');
        ops.push_back(op);
        p = (2 * p + s) % n;
        if (p == 0)
            break; // reached top early; remaining bits can be ignored
    }

    cout << ops.size() << '\n' << ops << '\n';
    return 0;
}
