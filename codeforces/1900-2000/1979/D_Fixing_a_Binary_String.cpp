#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve2() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int c0 = 0;
    int r = n - 1;
    int pos = -1;
    for (int l = n - 1; l >= 0; l--) {
        if (s[l] == '0') {
            c0++;
        }

        if (r - l + 1 == k && (c0 == k || c0 == 0)) {
            pos = r;
            break;
        }

        if (r - l + 1 == k) {
            if (s[r] == '0') {
                c0--;
            }
            r--;
        }
    }

    if (pos == -1) {
        cout << -1 << '\n';
        return;
    }

    int tt = pos;
    while (pos - k >= 0) {
        bool f = true;
        for (int i = 0; i < k; i++) {
            if (pos - i - k < 0 || s[pos - i] == s[pos - i - k]) {
                f = false;
            }
        }

        if (!f) {
            break;
        }
        pos -= k;
    }

    int L = pos - k + 1;
    if (L == 0) {
        if (tt == n - 1)
            cout << n << '\n';
        else {
            cout << -1 << '\n';
        }
        return;
    }

    string t = s.substr(0, L);
    string new_s = s.substr(L);

    ranges::reverse(t);
    new_s += t;


    // if (k == 1) {
    //     cout << "new s is: " << new_s << '\n';
    //     cout << "L is :" << L << '\n';
    // }


    for (int i = 0; i + k < n; i++) {
        if (new_s[i] == new_s[i + k]) {
            cout << -1 << '\n';
            return;
        }
    }

    cout << L << '\n';
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(long long x, long long y) { return uniform_int_distribution<int>(x, y)(rng); }

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
    int n;
    vector<__int128> P, H, HR;

    HashSeq(string s) {
        n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;

        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;

        HR.resize(n + 1);
        HR[0] = 0;
        for (int i = 1; i <= n; i++) {
            HR[i] = (HR[i - 1] * BASE + (s[n - i] ^ 7)) % MOD;
        }
    }

    long long query(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (H[r] - (H[l - 1] * P[r - l + 1]) % (__int128) MOD);
        long long ans = (long long) ((res + (__int128) MOD) % (__int128) MOD);
        return ans;
    }

    long long query_rev_on_reversed(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (HR[r] - (HR[l - 1] * P[r - l + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }

    long long query_rev_sub(int l, int r) const {
        if (l > r)
            return 0;
        int L = n - r + 1;
        int R = n - l + 1;
        __int128 res = (HR[R] - (HR[L - 1] * P[R - L + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string s1(n, '.'), s2(n, '.');
    for (int i = 0; i < n; i++) {
        s1[i] = ((i / k) % 2 == 0 ? '0' : '1');
        s2[i] = ((i / k) % 2 == 0 ? '1' : '0');
    }

    HashSeq hs1(s1), hs2(s2), hs(s);
    int val1 = hs1.query(1, n);
    int val2 = hs2.query(1, n);


    for (int pos = 1; pos <= n; pos++) {
        long long valL = hs.query_rev_sub(1, pos);
        long long valR = (pos == n) ? 0LL : hs.query(pos + 1, n);

        __int128 total128 = ((__int128) valR * hs.P[pos] + (__int128) valL) % (__int128) MOD;
        long long total = (long long) total128;

        if (total == val1 || total == val2) {
            cout << pos << '\n';
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
