#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
using ll = long long;
constexpr int MOD = int(1e9 + 7);

// 矩阵乘法，缓存友好版本。先算一整行的

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

Matrix quick_mul(Matrix mat, long long n) {
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


// 斐波那契，1 - index。 f1 = f2 = 1, f3 = 2, f4 = 3...
void fib(int n) {
    auto mat1 = Matrix(1, vector<Z>(2, 0));
    mat1[0][0] = 1;
    auto mat2 = Matrix{{1, 1}, {1, 0}};

    auto mat_pow = quick_mul(mat2, n - 1);
    auto mat3 = mat_mul(mat1, mat_pow);

    Z ans = mat3[0][0];
}


// lc3337 调用示例
class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int> &nums) {
        int SIZE = 26;
        Matrix mat(SIZE, vector<Z>(SIZE, 0));
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int m = nums[i];
            for (int j = 0; j < m; ++j) {
                mat[(i + j + 1) % SIZE][i] += 1;
            }
        }

        mat = quick_mul(mat, t);

        Matrix mat2(SIZE, vector<Z>(1, 0));
        for (char c: s) {
            mat2[c - 'a'][0] += 1;
        }

        mat = mat_mul(mat, mat2);

        Z total = 0;
        for (int i = 0; i < SIZE; ++i) {
            total += mat[i][0];
        }
        return (int) total;
    }
};
