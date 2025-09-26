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

constexpr int N = 500'005;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    explicit Comb(int n) : Comb() { init(n); }

    void init(int m) {
        if (m <= n) {
            return;
        }
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Z C(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(m) * invfac(n - m);
    }
    Z A(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(n - m);
    }
} comb(N);


void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    Z ans = 1;
    Z have = 0;

    int m = (n + 1) / 2;
    for (int i = n; i >= 1; i--) {
        if (i == m) {
            if (n & 1) {
                have++;
            } else {
                have += 2;
            }
        } else if (i < m) {
            have += 2;
        }

        if (int(have) && i > m) {
            ans = 0;
            break;
        }

        if (i == 1 && a[i] < 2) {
            ans = 0;
        }

        if (int(have) < a[i]) {
            ans = 0;
            break;
        }

        ans *= comb.C(int(have), a[i]);
        have -= a[i];
    }

    if (int(have)) {
        ans = 0;
    }

    cout << (int) ans << '\n';
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
