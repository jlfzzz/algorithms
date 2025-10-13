#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 1'000'005;

struct EulerSieve {
public:
    int n;
    vector<int> phi;
    vector<int> mu;
    vector<int> nextp; // min prime factor
    vector<int> prime;
    vector<char> is_prime;

    EulerSieve() : n(0) {}
    EulerSieve(int n) : n(n) { init(n); }

    void init(int n) {
        phi.assign(n, 1);
        mu.assign(n, 1);
        nextp.assign(n, 1);
        is_prime.assign(n, true);
        prime.clear();
        prime.reserve(1.2 * n / log(n));

        is_prime[1] = false;
        phi[1] = 1;
        mu[1] = 1;
        nextp[1] = 1;

        for (int i = 2; i < n; i++) {
            if (is_prime[i]) {
                prime.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
                nextp[i] = i;
            }
            for (int j = 0; j < (int) prime.size() && 1LL * i * prime[j] < n; j++) {
                int p = prime[j];
                int num = i * p;
                is_prime[num] = false;
                nextp[num] = p;
                if (i % p == 0) {
                    phi[num] = phi[i] * p;
                    mu[num] = 0;
                    break;
                } else {
                    phi[num] = phi[i] * (p - 1);
                    mu[num] = -mu[i];
                }
            }
        }
    }

    int get_Phi(int x) const {
        int res = x;
        for (int p = 2; x != 1; p += 1) {
            if (x % p == 0) {
                res = res / p * (p - 1);
                while (x % p == 0) {
                    x /= p;
                }
            }
        }
        return res;
    }

    int get_phi(int x) const { return phi[x]; }

    int get_mu(int x) const { return mu[x]; }

    int get_nextp(int x) const { return nextp[x]; }

    bool isprime(int x) const { return is_prime[x]; }

    const vector<int> &get_primes() const { return prime; }
} sieve(N);
