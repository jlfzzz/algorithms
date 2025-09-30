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

    vector<int> a(n + 1);
    rd_vec(a, 1);


    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] > 2) {
            prt("NO");
            return;
        }
    }

    vector<int> p1(n + 1), p2(n + 1);
    set<int> st1, st2;

    // for (int x: a) {
    //     debug("x is:", x);
    // }

    for (int i = 1; i <= n; i++) {
        st1.insert(i);
    }

    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (!st1.contains(x)) {
            p2[i] = x;
            st2.insert(x);
        } else {
            p1[i] = x;
            st1.erase(x);
        }
    }

    vector<pii> temp1;
    for (int i = 1; i <= n; i++) {
        if (p1[i])
            temp1.emplace_back(p1[i], i);
    }
    sort(temp1.begin(), temp1.end());

    set<int> can;
    for (int i = 1; i <= n; i++) {
        if (!st2.contains(i)) {
            can.insert(i);
        }
    }

    for (int i = (int) temp1.size() - 1; i >= 0; i--) {
        auto [x, id] = temp1[i];
        if (!p2[id]) {
            auto it = can.upper_bound(x);
            if (it == can.begin()) {
                prt("NO");
                return;
            }
            --it;
            p2[id] = *it;
            can.erase(it);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!p1[i]) {
            auto it = st1.upper_bound(p2[i]);
            if (it == st1.begin()) {
                prt("NO");
                return;
            }
            --it;
            p1[i] = *it;
            st1.erase(it);
        }
    }

    {
        vector<int> used(n + 1);
        for (int i = 1; i <= n; i++) {
            if (p1[i] < 1 || p1[i] > n) {
                prt("NO");
                return;
            }
            used[p1[i]]++;
            if (used[p1[i]] > 1) {
                prt("NO");
                return;
            }
        }
        fill(used.begin(), used.end(), 0);
        for (int i = 1; i <= n; i++) {
            if (p2[i] < 1 || p2[i] > n) {
                prt("NO");
                return;
            }
            used[p2[i]]++;
            if (used[p2[i]] > 1) {
                prt("NO");
                return;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (max(p1[i], p2[i]) != a[i]) {
            prt("NO");
            return;
        }
    }

    prt("YES");
    prt_vec(p1, 1);
    prt_vec(p2, 1);
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
