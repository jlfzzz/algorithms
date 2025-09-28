#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

// rank30+
// 傻逼t2花的时间比t3,t4都多，不然rank20以内

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

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int d = r - l + 1;
        Matrix m1(d, vector<Z>(d)), m2(d, vector<Z>(d));

        for (int i = 0; i < d; i++) {
            for (int j = 0; j < i; j++) {
                m1[i][j] = 1;
            }
        }

        for (int i = 0; i < d; i++) {
            for (int j = d - 1; j > i; j--) {
                m2[i][j] = 1;
            }
        }

        Matrix m0(1, vector<Z>(d, 1));

        int tn = n;
        tn--;

        int ttn = tn / 2;

        auto m12 = mat_mul(m1, m2);
        // 先增
        auto m12_pow = quick_mul(m12, ttn);
        if (tn & 1) {
            m12_pow = mat_mul(m12_pow, m1);
        }

        auto m3 = mat_mul(m0, m12_pow);
        Z ans = 0;
        for (auto &v: m3) {
            for (auto x: v) {
                ans += x;
            }
        }

        auto m21 = mat_mul(m2, m1);
        auto m21_pow = quick_mul(m21, ttn);
        if (tn & 1) {
            m21_pow = mat_mul(m21_pow, m2);
        }

        auto m4 = mat_mul(m0, m21_pow);
        for (auto &v: m4) {
            for (auto x: v) {
                ans += x;
            }
        }

        return (int) ans;
    }
};


class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        vector<Z> dp1(r + 1), dp2(r + 1);

        for (int i = l; i <= r; i++) {
            dp1[i] = dp2[i] = 1;
        }

        // ji数 1 是 峰，2 谷
        for (int i = 1; i < n; i++) {
            vector<Z> ndp1(r + 1), ndp2(r + 1);

            if (i % 2 == 1) {
                Z pre = dp1[l];
                for (int j = l + 1; j <= r; j++) {
                    ndp1[j] = pre;
                    pre += dp1[j];
                }

                pre = dp2[r];
                for (int j = r - 1; j >= l; j--) {
                    ndp2[j] = pre;
                    pre += dp2[j];
                }
            } else {
                Z pre = dp1[r];
                for (int j = r - 1; j >= l; j--) {
                    ndp1[j] = pre;
                    pre += dp1[j];
                }

                pre = dp2[l];
                for (int j = l + 1; j <= r; j++) {
                    ndp2[j] = pre;
                    pre += dp2[j];
                }
            }

            dp1 = std::move(ndp1);
            dp2 = std::move(ndp2);
        }

        Z ans = 0;
        for (int i = l; i <= r; i++) {
            ans += dp1[i] + dp2[i];
        }

        return (int) ans;
    }
};

class Solution {
public:
    long long splitArray(vector<int> &nums) {
        int n = nums.size();
        vector<bool> suf(n + 1);
        vector<ll> suf_s(n + 1);
        int mx = -1;
        for (int i = n - 1; i >= 0; i--) {
            ll x = nums[i];
            if (x <= mx) {
                break;
            }

            suf[i] = true;
            mx = x;
        }

        for (int i = n - 1; i >= 0; i--) {
            suf_s[i] = suf_s[i + 1] + nums[i];
        }

        ll ans = 1e16 + 5;
        mx = -1;
        ll pre = 0;
        for (int i = 0; i < n; i++) {
            ll x = nums[i];
            pre += x;
            if (x <= mx) {
                break;
            }
            if (!suf[i + 1]) {
                mx = x;
                continue;
            }

            ans = min(ans, abs(pre - suf_s[i + 1]));
            mx = x;
        }

        if (ans == 1e16 + 5) {
            ans = -1;
        }

        return ans;
    }
};

class Solution {
public:
    vector<int> decimalRepresentation(int n) {
        vector<int> ans;
        while (n) {
            string s = to_string(n);
            int m = s.size();

            int t = 1;
            for (int i = 0; i < m - 1; i++) {
                t *= 10;
            }

            t = (s[0] - '0') * t;
            ans.push_back(t);
            n -= t;
        }

        return ans;
    }
};
