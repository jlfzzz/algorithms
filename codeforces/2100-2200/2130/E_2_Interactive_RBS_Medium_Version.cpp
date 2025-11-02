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

    auto ask0 = [&](int i, int j) -> int {
        cout << "? 2 " << i << ' ' << j << endl;
        int t;
        rd(t);
        return t;
    };

    auto ask1 = [&](int l, int r) -> int {
        int k = r - l + 1;
        cout << "? " << k << " ";
        F(i, l, r) { cout << i << " "; }
        cout << endl;
        int t;
        rd(t);
        return t;
    };

    int total = ask1(1, n);
    int left = -1, right = -1;
    if (total == 0) {
        left = n;
        right = 1;
    } else {
        int l = 1;
        int r = n + 1;
        int ans = 0;
        while (l < r) {
            int mid = (l + r) / 2;
            int t = ask1(1, mid);
            if (t > 0) {
                ans = mid;
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        left = ans - 1;
        right = ans;
    }

    string ans(n + 1, '(');
    for (int i = 1; i <= n; i += 8) {
        if (i + 8 > n) {
            F(j, i, n) {
                int t = ask0(left, j);
                if (t) {
                    ans[j] = ')';
                }
            }
        } else {
            int cnt = 0;
            vi temp;
            int l = i;
            int total = 0;
            F(j, 1, 8) {
                F(k, 1, cnt) {
                    temp.pb(left);
                    temp.pb(right);
                }
                temp.pb(left);
                temp.pb(l);
                temp.pb(left);

                total += cnt * (cnt + 1) / 2;

                l++;
                cnt = cnt * 2 + 1;
            }

            cout << "? " << temp.size() << " ";
            for (int x: temp) {
                cout << x << " ";
            }
            cout << endl;

            int res;
            rd(res);
            int d = res - total;
            F(j, 0, 10) {
                if (d >> j & 1) {
                    ans[i + j] = ')';
                }
            }
        }
    }

    ans = ans.substr(1);
    cout << "! " << ans << endl;
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
