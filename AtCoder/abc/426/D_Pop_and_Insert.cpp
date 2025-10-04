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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    string s;
    rd(s);

    auto f = [&](const string &str, char target) -> int {
        bool flag = true;
        for (char c: str)
            if (c != target) {
                flag = false;
                break;
            }
        if (flag)
            return 0;

        struct Info {
            char c;
            int len;
        };
        vector<Info> temp;
        {
            int i = 0, N = str.size();
            while (i < N) {
                int j = i;
                while (j < N && str[j] == str[i])
                    j++;
                temp.push_back(Info{str[i], j - i});
                i = j;
            }
        }

        deque<Info> dq(temp.begin(), temp.end());
        int ans = 0;
        while (true) {
            if (dq.size() == 1) {
                break;
            }
            if (dq.front().c != target) {
                ans += dq.front().len;
                dq.pop_front();
                continue;
            }
            if (dq.back().c != target) {
                ans += dq.back().len;
                dq.pop_back();
                continue;
            }

            int L = min(dq.front().len, dq.back().len);
            ans += 2 * L;
            if (dq.front().len < dq.back().len) {
                dq.pop_front();
            } else if (dq.front().len > dq.back().len) {
                dq.pop_back();
            } else {
                dq.pop_back();
            }
        }
        return ans;
    };

    int ans0 = f(s, '0');
    int ans1 = f(s, '1');
    int ans = min(ans0, ans1);
    prt(ans);
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
