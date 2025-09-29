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
    void read(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void read(T &x, Args &...args) {
        cin >> x;
        read(args...);
    }

    template<typename A, typename B>
    void read(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void read_vec(vector<T> &v) {
        for (auto &x: v) {
            read(x);
        }
    }

    template<typename T>
    void read_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 0;

void init() {}

void solve() {
    int n, m, d;
    read(n, m, d);

    vector<int> dp(n + 1);

    int pre_t;
    {
        int a, b, t;
        read(a, b, t);
        pre_t = t;
        for (int i = 1; i <= n; i++) {
            int diff = abs(a - i);
            dp[i] = b - diff;
        }
    }


    For(_, m - 1) {
        int a, b, t;
        read(a, b, t);

        vector<int> ndp(n + 1, -inf);
        int dt = t - pre_t;
        pre_t = t;

        int r = min(dt * d, n);

        deque<int> dq;

        int R = min(n, 1 + r);
        for (int j = 1; j <= R; j++) {
            while (!dq.empty() && dp[dq.back()] <= dp[j])
                dq.pop_back();
            dq.push_back(j);
        }

        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                while (!dq.empty() && dq.front() < i - r)
                    dq.pop_front();
                int add = i + r;
                if (add <= n) {
                    while (!dq.empty() && dp[dq.back()] <= dp[add])
                        dq.pop_back();
                    dq.push_back(add);
                }
            }

            int best = dq.empty() ? -inf : dp[dq.front()];
            ndp[i] = best + b - abs(a - i);
        }

        dp = std::move(ndp);
    }

    int ans = -inf;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }

    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        read(T);
    }
    while (T--)
        solve();
    return 0;
}
