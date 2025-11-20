#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
    }

    template<typename T>
    void prt(const T &x) {
        cout << x << '\n';
    }

    template<typename T, typename... Args>
    void prt(const T &first, const Args &...rest) {
        cout << first;
        ((cout << ' ' << rest), ...);
        cout << '\n';
    }

    template<typename T>
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
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
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    string s;
    rd(s); 

    // 预处理 L 和 R 的连续长度
    // s[i] 对应题解中的 "第 i+1 个字符"
    // 数组大小为 n 足够, 因为 s 的索引只到 n-2
    vi left_L(n, 0), left_R(n, 0), right_L(n, 0), right_R(n, 0);

    // 从左到右计算
    F(i, 0, n - 2) {
        if (s[i] == 'L') {
            left_L[i] = (i > 0 ? left_L[i - 1] : 0) + 1;
        } else {
            left_R[i] = (i > 0 ? left_R[i - 1] : 0) + 1;
        }
    }

    // 从右到左计算
    D(i, n - 2, 0) {
        if (s[i] == 'L') {
            right_L[i] = (i < n - 2 ? right_L[i + 1] : 0) + 1;
        } else {
            right_R[i] = (i < n - 2 ? right_R[i + 1] : 0) + 1;
        }
    }

    // 差分数组 (1-indexed, C[1] 到 C[n], C[n+1] 用于差分)
    vi C(n + 2, 0);

    // 遍历每个数字 i (1-indexed, 1...n)
    F(i, 1, n) {
        // 题解中的 "第 (i-1) 个字符" 对应 s[i-2]
        // 题解中的 "第 i 个字符" 对应 s[i-1]

        // 处理边界: i=1 时 i-2 < 0; i=n 时 i-1 = n-1 (越界)
        int run_Rs_left = (i - 2 >= 0) ? left_R[i - 2] : 0;
        int run_Ls_right = (i - 1 <= n - 2) ? right_L[i - 1] : 0;

        int run_Ls_left = (i - 2 >= 0) ? left_L[i - 2] : 0;
        int run_Rs_right = (i - 1 <= n - 2) ? right_R[i - 1] : 0;

        // 根据 Theorem 2 计算 l 和 r
        int l = run_Rs_left + run_Ls_right + 1;
        int r = n - (run_Ls_left + run_Rs_right);

        // 应用到差分数组
        C[l]++;
        C[r + 1]--;
    }

    // 计算前缀和, C[k] 将存储位置 k 的答案
    F(k, 1, n) { C[k] += C[k - 1]; }

    // 收集 C[1]...C[n] 到答案 vector
    vi ans;
    F(k, 1, n) { ans.pb(C[k]); }
    prv(ans); // 使用模板的打印函数
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
