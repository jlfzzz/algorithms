#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
// #define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}
template<int MOD_>
struct modnum {
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");

private:
    using ll = long long;

    int v;

    static int minv(int a, int m) {
        a %= m;
        assert(a);
        return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
    }

public:
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD)) {
        if (v < 0)
            v += MOD;
    }
    explicit operator int() const { return v; }
    friend std::ostream &operator<<(std::ostream &out, const modnum &n) { return out << int(n); }
    friend std::istream &operator>>(std::istream &in, modnum &n) {
        ll v_;
        in >> v_;
        n = modnum(v_);
        return in;
    }

    friend bool operator==(const modnum &a, const modnum &b) { return a.v == b.v; }
    friend bool operator!=(const modnum &a, const modnum &b) { return a.v != b.v; }

    modnum inv() const {
        modnum res;
        res.v = minv(v, MOD);
        return res;
    }
    friend modnum inv(const modnum &m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD - v : 0;
        return res;
    }
    friend modnum neg(const modnum &m) { return m.neg(); }

    modnum operator-() const { return neg(); }
    modnum operator+() const { return modnum(*this); }

    modnum &operator++() {
        v++;
        if (v == MOD)
            v = 0;
        return *this;
    }
    modnum &operator--() {
        if (v == 0)
            v = MOD;
        v--;
        return *this;
    }
    modnum &operator+=(const modnum &o) {
        v += o.v;
        if (v >= MOD)
            v -= MOD;
        return *this;
    }
    modnum &operator-=(const modnum &o) {
        v -= o.v;
        if (v < 0)
            v += MOD;
        return *this;
    }
    modnum &operator*=(const modnum &o) {
        v = int(ll(v) * ll(o.v) % MOD);
        return *this;
    }
    modnum &operator/=(const modnum &o) { return *this *= o.inv(); }

    friend modnum operator++(modnum &a, int) {
        modnum r = a;
        ++a;
        return r;
    }
    friend modnum operator--(modnum &a, int) {
        modnum r = a;
        --a;
        return r;
    }
    friend modnum operator+(const modnum &a, const modnum &b) { return modnum(a) += b; }
    friend modnum operator-(const modnum &a, const modnum &b) { return modnum(a) -= b; }
    friend modnum operator*(const modnum &a, const modnum &b) { return modnum(a) *= b; }
    friend modnum operator/(const modnum &a, const modnum &b) { return modnum(a) /= b; }
};

using Z = modnum<MOD>;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    For(i, n) a[i] &= 1;

    vector<vector<Z>> dp(4, vector<Z>(5));

    for (int i = 0; i < n; i++) {
        auto ndp = dp;
        if (a[i] == 1) {
            ndp[3][2] += dp[2][2] + dp[3][1];
            ndp[3][3] += dp[2][3] + dp[3][2];

            ndp[2][1] += dp[1][1];
            ndp[2][3] += dp[1][3];

            ndp[1][1] += 1;
            ndp[1][2] += 1;
        } else {
            ndp[3][0] += dp[2][0] + dp[3][0];
            ndp[3][1] += dp[2][1] + dp[3][3];

            ndp[2][0] += dp[1][0];
            ndp[2][2] += dp[1][2];

            ndp[1][0] += 1;
            ndp[1][3] += 1;
        }
        dp = std::move(ndp);
    }

    Z ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += dp[3][i];
    }

    cout << (int) ans << '\n';
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

void solve2() {
    int n;
    cin >> n;
    vector<Z> a(n + 1);
    For(i, n) {
        int x;
        cin >> x;
        a[i + 1] = x & 1;
    }

    int cnt0 = 0;
    for (int i = 1; i <= n; i++)
        if ((int) a[i] == 0)
            cnt0++;
    int cnt1 = n - cnt0;

    vector<int> suf1(n + 2), suf0(n + 2);
    for (int i = n; i >= 1; i--) {
        suf1[i] = suf1[i + 1] + (((int) a[i]) == 1);
        suf0[i] = suf0[i + 1] + (((int) a[i]) == 0);
    }

    Z eo = 0, oe = 0;
    for (int i = 1; i <= n; i++) {
        if (((int) a[i]) == 0)
            eo += suf1[i + 1];
        else
            oe += suf0[i + 1];
    }
    Z oo = Z(1LL * cnt1 * (cnt1 - 1) / 2);

    vector<vector<Z>> dp_eoo(n + 1, vector<Z>(3));
    for (int i = 1; i <= n; i++) {
        dp_eoo[i] = dp_eoo[i - 1];
        int p = (int) a[i];
        if (p == 0) {
            dp_eoo[i][1] += 1;
            dp_eoo[i][1] += dp_eoo[i - 1][0];
        } else {
            dp_eoo[i][2] += dp_eoo[i - 1][1];
            dp_eoo[i][0] += dp_eoo[i - 1][2];
        }
    }
    Z s_eoo = dp_eoo[n][0] + dp_eoo[n][1] + dp_eoo[n][2];

    vector<vector<Z>> dp_ooe(n + 1, vector<Z>(3));
    for (int i = 1; i <= n; i++) {
        dp_ooe[i] = dp_ooe[i - 1];
        int p = (int) a[i];
        if (p == 1) {
            dp_ooe[i][1] += 1;
            dp_ooe[i][1] += dp_ooe[i - 1][0];
            dp_ooe[i][2] += dp_ooe[i - 1][1];
        } else {
            dp_ooe[i][0] += dp_ooe[i - 1][2];
        }
    }
    Z s_ooe = dp_ooe[n][0] + dp_ooe[n][1] + dp_ooe[n][2];

    vector<vector<Z>> dp_oeo(n + 1, vector<Z>(3));
    for (int i = 1; i <= n; i++) {
        dp_oeo[i] = dp_oeo[i - 1];
        int p = (int) a[i];
        if (p == 1) {
            dp_oeo[i][1] += 1;
            dp_oeo[i][1] += dp_oeo[i - 1][0];
            dp_oeo[i][0] += dp_oeo[i - 1][2];
        } else {
            dp_oeo[i][2] += dp_oeo[i - 1][1];
        }
    }
    Z s_oeo = dp_oeo[n][0] + dp_oeo[n][1] + dp_oeo[n][2];

    Z ans = 0;
    ans += s_eoo - Z(cnt0) - eo;
    ans += s_ooe - Z(cnt1) - oo;
    ans += s_oeo - Z(cnt1) - oe;

    Z ooo = q_pow(Z(2), cnt0) - 1 - Z(cnt0) - Z(1LL * cnt0 * (cnt0 - 1) / 2);
    ans += ooo;

    cout << (int) ans << '\n';
}
