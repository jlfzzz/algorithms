#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

const int N = 1e7 + 5;

struct Sieve {
    bool is_not_prime[N + 1];
    std::vector<int> primes;
    int distinct_factors_count[N + 1];
    int total_factors_count[N + 1];

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        distinct_factors_count[1] = 0;
        total_factors_count[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                distinct_factors_count[i] = 1;
                total_factors_count[i] = 1;
            }

            for (int p: primes) {
                if ((long long) i * p > n) {
                    break;
                }

                is_not_prime[i * p] = true;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];
                    total_factors_count[i * p] = total_factors_count[i] + 1;
                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;
                    total_factors_count[i * p] = total_factors_count[i] + 1;
                }
            }
        }
    }

    bool is_prime(int x) const {
        if (x < 0 || x > N)
            return false; // 范围检查
        return !is_not_prime[x];
    }
};

void init() {}
Sieve sieve;
void solve() {
    int n;
    cin >> n;


    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if (sieve.is_prime(i)) {
            ans++;
        } else {
            ans += sieve.distinct_factors_count[i];
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
