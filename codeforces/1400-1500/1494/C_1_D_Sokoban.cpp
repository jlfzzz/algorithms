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
    int n, m;
    rd(n, m);

    vi box(n), a(m);
    rv(box);
    rv(a);


    vi v1, v2;
    F(i, 0, n - 1) {
        if (box[i] > 0) {
            v1.pb(box[i]);
        }
    }
    F(i, 0, m - 1) {
        if (a[i] > 0) {
            v2.pb(a[i]);
        }
    }

    ranges::sort(v1);
    ranges::sort(v2);

    auto calc = [&](vi &v1, vi &v2) -> int {
        int ans = 0;
        set<int> st(all(v2));
        set<int> mark;
        int n = v1.size();
        int m = v2.size();

        int suf = 0;
        for (int x: v1) {
            if (st.contains(x)) {
                suf++;
                mark.insert(x);
            }
        }

        set<int> window;
        int len = 0;
        v1.pb(1e9 + 5);
        int p2 = 0;
        while (p2 < m && v2[p2] < v1[0]) {
            p2++;
        }
        F(i, 0, n - 1) {
            int cur = v1[i];
            if (mark.contains(cur)) {
                suf--;
            }
            len++;
            while (p2 < m && v2[p2] < v1[i + 1]) {
                int pos = v2[p2];
                window.insert(pos);
                while (pos - *window.begin() + 1 > len) {
                    window.erase(window.begin());
                }
                ans = max<int>(ans, window.size() + suf);
                p2++;
            }
        }

        return ans;
    };

    int ans = calc(v1, v2);
    v1.clear();
    v2.clear();
    F(i, 0, n - 1) {
        if (box[i] < 0) {
            v1.pb(-box[i]);
        }
    }
    F(i, 0, m - 1) {
        if (a[i] < 0) {
            v2.pb(-a[i]);
        }
    }

    ranges::sort(v1);
    ranges::sort(v2);
    ans += calc(v1, v2);

    prt(ans);
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
