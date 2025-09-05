#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}
const int N = 1e4 + 5;

struct Sieve {
    bool is_not_prime[N + 1];
    std::vector<int> primes;
    int min_prime_factor[N + 1];
    int distinct_factors_count[N + 1];

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        min_prime_factor[0] = min_prime_factor[1] = 0;
        distinct_factors_count[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                min_prime_factor[i] = i;
                distinct_factors_count[i] = 1;
            }

            for (int p: primes) {
                if ((long long) i * p > n)
                    break;
                is_not_prime[i * p] = true;
                min_prime_factor[i * p] = p;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];
                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;
                }
            }
        }
    }

    bool is_prime(int x) const {
        if (x <= 1 || x > N)
            return false;
        return !is_not_prime[x];
    }
};
Sieve s;
void solve() {
    int x;
    cin >> x;


    for (int y = 1; y < x; y++) {
        int t = y ^ x;
        if (t > 1 && !s.is_prime(t)) {
            cout << y << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
