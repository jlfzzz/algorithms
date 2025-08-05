#include <bits/stdc++.h>
#include <type_traits>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

vector<bool> comp(1e5 + 1);
vector<int> primes;

void sieve() {
    for (int i = 2; i * i <= 1e5; i++)
        if (!comp[i])
            for (int j = i * i; j <= 1e5; j += i)
                comp[j] = true;
    for (int i = 2; i <= 1e5; i++)
        if (!comp[i])
            primes.push_back(i);
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (auto it = primes.rbegin(); it != primes.rend(); ++it) {
        vector<int> cycle;
        for (int i = *it; i <= n; i += *it)
            if (!p[i])
                cycle.push_back(i);
        for (int i = 0; i < cycle.size(); i++)
            p[cycle[i]] = cycle[(i + 1) % cycle.size()];
    }
    for (int i = 1; i <= n; i++)
        if (!p[i])
            p[i] = i;
    for (int i = 1; i <= n; i++)
        cout << p[i] << (i != n ? ' ' : '\n');
}

int main() {
    sieve();
    int t;
    cin >> t;
    while (t--)
        solve();
}
