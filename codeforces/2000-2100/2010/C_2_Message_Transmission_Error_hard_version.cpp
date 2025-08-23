#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
// constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(long long x, long long y) { return uniform_int_distribution<int>(x, y)(rng); }

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
    vector<__int128> P, H;

    HashSeq(string s) {
        int n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;
        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
    }

    long long query(int l, int r) { return (H[r] - H[l - 1] * P[r - l + 1] % MOD + MOD) % MOD; }
};

void solve2() {
    string t;
    cin >> t;

    int n = t.size();
    HashSeq hs(t);
    for (int i = (n - 1) / 2; i > 0; i--) {
        int len = n - i;
        if (hs.query(1, len) == hs.query(i + 1, n)) {
            cout << "YES\n";
            cout << t.substr(0, len) << '\n';
            return;
        }
    }

    cout << "NO\n";
}

void solve() {
    string t;
    cin >> t;

    int n = t.size();
    vector<int> nxt(n, 0);
    int i = 1, len = 0;
    while (i < n) {
        while (len && t[i] != t[len]) {
            len = nxt[len - 1];
        }

        if (t[i] == t[len]) {
            len++;
        }
        nxt[i] = len;
        i++;
    }

    if (nxt[n - 1] * 2 > n) {
        cout << "YES\n";
        cout << t.substr(0, nxt[n - 1]) << '\n';
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
