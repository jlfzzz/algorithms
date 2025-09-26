#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

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

Z q_pow(Z base, long long exp) {
    Z result(1);
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}
const int N = 500'005;

vector<Z> fac(N), ifac(N);

void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * Z(i);
    ifac[N - 1] = fac[N - 1].inv();
    for (int i = N - 2; i >= 1; --i)
        ifac[i] = ifac[i + 1] * Z(i + 1);
}

// O(a)
Z C_large(int n, int a) {
    if (a < 0)
        return {0};
    if (n < a)
        return {0};
    Z res = 1;
    for (int i = 0; i < a; ++i) {
        Z term = n - i;
        res = res * term;
    }
    res = res * ifac[a];
    return res;
}

Z C(int n, int k) {
    if (k < 0 || k > n)
        return {0};
    return fac[n] * ifac[k] * ifac[n - k];
}
void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (k & 1) {
        cout << 1 << '\n';
        return;
    }

    vector<int> sz(n + 1);
    Z sum = 0;
    int m = k >> 1;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            dfs(v, u);
            sum += C(sz[v], m) * C(n - sz[v], m);
            sz[u] += sz[v];
        }
    };

    dfs(1, -1);

    Z total = C(n, k);
    Z ans = (total + sum) / total;

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
