#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

constexpr int MOD = int(1e9 + 7);

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

class Solution {
public:
    int countCoprime(vector<vector<int>> &mat) {
        int m = (int) mat.size();
        int n = (int) mat[0].size();

        int mx = 0;
        for (auto &v: mat)
            for (int x: v)
                mx = max(mx, x);

        vector<Z> ways(mx + 1);

        for (int d = 1; d <= mx; d++) {
            Z prod = Z(1);
            for (int i = 0; i < m; i++) {
                int cnt = 0;
                for (int x: mat[i])
                    if (x % d == 0)
                        cnt++;
                if (cnt == 0) {
                    prod = Z(0);
                    break;
                }
                prod *= Z(cnt);
            }
            ways[d] = prod;
        }

        for (int d = mx; d >= 1; d--) {
            for (int k = 2 * d; k <= mx; k += d) {
                ways[d] -= ways[k];
            }
        }

        return int(ways[1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
