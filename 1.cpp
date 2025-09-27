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

const int MAXN = 5000;
int M;

vector<int> primes;

void sieve() {
    vector<bool> isprime(MAXN + 1, true);
    for (int i = 2; i <= MAXN; i++) {
        if (isprime[i])
            primes.push_back(i);
        for (int p: primes) {
            if (i * p > MAXN)
                break;
            isprime[i * p] = false;
            if (i % p == 0)
                break;
        }
    }
}

int count_fact(int n, int p) {
    int cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

int mod_pow(int a, int e, int mod) {
    int res = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1)
            res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

void solve() {
    int N;
    cin >> N;
    vector<int> C(N);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> C[i];
        sum += C[i];
    }

    map<int, int> cnt;
    for (int p: primes) {
        if (p > sum)
            break;
        int e = count_fact(sum, p);
        for (int x: C)
            e -= count_fact(x, p);
        if (e > 0)
            cnt[p] = e;
    }

    int ans = 1;
    for (auto [p, e]: cnt) {
        ans = ans * mod_pow(p, e, M) % M;
    }

    cout << ans % M << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    sieve();
    int T = 1;
    cin >> T;
    cin >> M;
    while (T--)
        solve();
    return 0;
}
