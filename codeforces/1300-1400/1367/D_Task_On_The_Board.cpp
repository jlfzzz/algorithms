#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
#define pb push_back
#define pf push_front
#define eb emplace_back
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
    string s;
    rd(s);

    int n = s.size();
    int m;
    rd(m);
    vector<int> diff(m);
    rd_vec(diff);

    vector<int> cnt(26);
    for (char c: s) {
        cnt[c - 'a']++;
    }

    int bigger = 0;

    auto check = [&](char mx) -> string {
        string temp(m, '0');
        set<int> pos;
        for (int i = 0; i < m; i++) {
            if (diff[i] == 0) {
                temp[i] = mx;
                pos.insert(i);
            }
        }

        int idx = mx - 'a';

        if (cnt[idx] < pos.size()) {
            return "";
        }

        int accu = cnt[idx] - pos.size() + bigger;
        for (int i = idx - 1; i >= 0; i--) {
            vector<int> now;
            for (int j = 0; j < m; j++) {
                if (pos.contains(j)) {
                    continue;
                }

                int d = 0;
                for (int x: pos) {
                    d += abs(x - j);
                }

                if (d == diff[j]) {
                    now.pb(j);
                }
            }

            if (now.size() <= cnt[i]) {
                for (int j: now) {
                    temp[j] = char('a' + i);
                    pos.insert(j);
                }
                accu += cnt[i] - now.size();
            } else {
                accu += cnt[i];
            }

            if (accu > n - m) {
                return "";
            }
        }

        return temp;
    };

    for (int i = 25; i >= 0; i--) {
        if (cnt[i]) {
            auto t = check(char(i + 'a'));
            if (t.size()) {
                prt(t);
                return;
            }
        }
        bigger += cnt[i];

        if (bigger > n - m) {
            break;
        }
    }

    prt("NO");
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
