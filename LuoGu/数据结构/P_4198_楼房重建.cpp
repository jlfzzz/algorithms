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
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
    }

    template<typename T>
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
    }

    template<typename A, typename B>
    void rd(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 0;

void init() {}

struct Seg {
    vector<long double> mx; // 区间最大斜率
    vector<int> sum;        // 区间内自左向右可见楼数量
    int n;

    Seg(int n) : mx(4 * n + 5, 0.0L), sum(4 * n + 5, 0), n(n) {}

    int dfs(int o, int l, int r, long double mls) {
        // 若当前区间最大斜率不超过已知最大斜率，则该区间贡献为 0
        if (mx[o] <= mls) return 0; // 剪枝
        if (l == r) return 1;       // 叶子：该点斜率一定大于 mls
        int mid = (l + r) / 2;
        int ls = o * 2, rs = o * 2 + 1;
        if (mx[ls] <= mls) return dfs(rs, mid + 1, r, mls);
        // 左侧一定能看到至少一个；右侧的可见数与“从左到右扫完整个左儿子后的 mls=mx[ls]”相同
        return dfs(ls, l, mid, mls) + (sum[o] - sum[ls]);
    }

    void pushup(int o, int l, int r) {
        int mid = (l + r) / 2;
        int ls = o * 2, rs = o * 2 + 1;
        mx[o] = max(mx[ls], mx[rs]);
        // 区间总可见数 = 左侧可见数 + 在右侧、已知 mls=mx[ls] 情况下可见数
        sum[o] = sum[ls] + dfs(rs, mid + 1, r, mx[ls]);
    }

    void change(int o, int l, int r, int i, long double val) {
        if (l == r) {
            mx[o] = val;
            sum[o] = (val > 0.0L) ? 1 : 0; // 本题 y>=1，恒为 1，这里写得更稳妥
            return;
        }
        int mid = (l + r) / 2;
        if (i <= mid) change(o * 2, l, mid, i, val);
        else change(o * 2 + 1, mid + 1, r, i, val);
        pushup(o, l, r);
    }
};

void solve() {
    int n, m;
    rd(n, m);

    Seg seg(n + 1);

    while (m--) {
        int x, y;
        rd(x, y);

        seg.change(1, 1, n, x, (long double) y / (long double) x);
        prt_endl(seg.sum[1]);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
