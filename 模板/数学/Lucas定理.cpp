#include <iostream>

using ll = long long;

constexpr int N = 1'000'005;
ll fact[N], invfact[N];

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n, ll mod) { return power(n, mod - 2, mod); }

void init(ll p) {
    fact[0] = 1;
    for (ll i = 1; i < p; i++) {
        fact[i] = fact[i - 1] * i % p;
    }
    invfact[p - 1] = modInverse(fact[p - 1], p);
    for (ll i = p - 2; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % p;
    }
}

ll combinations(ll n, ll k, ll p) {
    if (k < 0 || k > n)
        return 0;
    return fact[n] * invfact[k] % p * invfact[n - k] % p;
}

ll lucas(ll n, ll k, ll p) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    return (lucas(n / p, k / p, p) * combinations(n % p, k % p, p)) % p;
}

void solve() {
    ll n, m, p;
    std::cin >> n >> m >> p;
    init(p);

    std::cout << lucas(n + m, n, p) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
