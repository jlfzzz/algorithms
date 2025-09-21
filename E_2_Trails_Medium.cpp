#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
// #define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
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

using Matrix = vector<vector<Z>>;

Matrix mat_mul(const Matrix &m1, const Matrix &m2) {
    int n = m1.size();
    int p = m1[0].size();
    int m = m2[0].size();

    Matrix ret(n, vector<Z>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < p; ++k) {
            if (m1[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < m; ++j) {
                ret[i][j] = ret[i][j] + m1[i][k] * m2[k][j];
            }
        }
    }
    return ret;
}

Matrix quick_mul(Matrix mat, int n) {
    int m = mat.size();
    Matrix unit(m, vector<Z>(m, 0));
    for (int i = 0; i < m; ++i) {
        unit[i][i] = 1;
    }

    while (n) {
        if (n & 1) {
            unit = mat_mul(unit, mat);
        }
        mat = mat_mul(mat, mat);
        n >>= 1;
    }
    return unit;
}

void solve() {
    int m, n;
    cin >> m >> n;

    vector<Z> s(m), l(m);
    For(i, m) cin >> s[i];
    For(i, m) cin >> l[i];

    Matrix mat1(1, vector<Z>(m));
    mat1[0][0] = 1;

    Matrix mat2(m, vector<Z>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            mat2[i][j] = s[i] * (s[j] + l[j]) + l[i] * s[j];
        }
    }

    auto mat3 = quick_mul(mat2, n);
    auto mat4 = mat_mul(mat1, mat3);

    Z ans = 0;

    for (int i = 0; i < m; i++) {
        ans += mat4[0][i];
    }

    cout << ans << '\n';
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
