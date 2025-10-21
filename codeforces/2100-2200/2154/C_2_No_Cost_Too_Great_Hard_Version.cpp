#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();

    for (int i = 2; i <= n; ++i) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }

        for (auto p: primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::map<int, int> cnt;
    for (auto x: a) {
        while (x > 1) {
            int p = minp[x];
            if (++cnt[p] > 1) {
                std::cout << 0 << "\n";
                return;
            }

            while (x % p == 0) {
                x /= p;
            }
        }
    }

    i64 ans = 0;
    if (cnt.contains(2)) {
        int pos = -1, minv = 2e9;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 == 0) {
                pos = i;
            } else {
                minv = std::min(minv, b[i]);
            }
        }

        ans = minv;
        for (auto &[p, _]: cnt) {
            if (a[pos] % p != 0) {
                ans = std::min(ans, (i64) b[pos] * ((i64) (a[pos] + p - 1) / p * p - a[pos]));
            }
        }
    } else {
        std::vector<std::pair<int, int>> c;
        for (int i = 0; i < n; ++i) {
            c.emplace_back(b[i], a[i]);
        }

        std::ranges::sort(c);
        ans = c[0].first + c[1].first;

        for (int i = 0; i < n; ++i) {
            int x = a[i] + 1;
            if (b[i] >= ans) {
                continue;
            }

            while (x > 1) {
                int p = minp[x];
                if (a[i] % p != 0 && cnt.contains(p)) {
                    ans = b[i];
                    break;
                }

                while (x % p == 0) {
                    x /= p;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            int x = a[i] + 2;
            if (2 * b[i] >= ans) {
                continue;
            }

            while (x > 1) {
                int p = minp[x];
                if (a[i] % p != 0 && cnt.contains(p)) {
                    ans = 2 * b[i];
                    break;
                }

                while (x % p == 0) {
                    x /= p;
                }
            }
        }

        int min = c[0].second, v = c[0].first;
        for (auto &[p, _]: cnt) {
            if (min % p != 0) {
                ans = std::min(ans, (i64) v * ((i64) (min + p - 1) / p * p - min));
            }
        }
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int t = 1;
    sieve(2e5 + 5);
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
