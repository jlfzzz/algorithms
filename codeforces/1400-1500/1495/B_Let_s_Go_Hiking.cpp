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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vi a(n);
    rv(a);

    int pos = -1;
    int mx = -1;

    int mx2 = -1;
    map<int, int> cnt;

    F(i, 0, n - 1) {
        if (i > 0 && i < n - 1 && a[i] > a[i - 1] && a[i] > a[i + 1]) {
            int j = i - 1;
            while (j >= 0 && a[j] - a[j + 1] < 0) {
                j--;
            }
            int left = i - j;
            j = i + 1;
            while (j < n && a[j] - a[j - 1] < 0) {
                j++;
            }
            int right = j - i;

            mx2 = max({mx2, left, right});
            cnt[left]++;
            cnt[right]++;

            if (left == right && (left % 2)) {
                if (pos == -1) {
                    pos = i;
                    mx = left;
                } else if (left > mx) {
                    mx = left;
                    pos = i;
                }
            }
        }
    }

    {
        int j = n - 2;
        while (j >= 0 && a[j] < a[j + 1]) {
            j--;
        }
        int len = n - 1 - j;
        cnt[len]++;
        // j = n - 2;
        // while (j >= 0 && a[j] > a[j + 1]) {
        //     j--;
        // }
        // len = n - 1 - j;
        // cnt[len]++;
    }
    {
        int j = 1;
        while (j < n && a[j] < a[j - 1]) {
            j++;
        }
        int len = j;
        cnt[len]++;
        // j = 1;
        // while (j < n && a[j] > a[j - 1]) {
        //     j++;
        // }
        // len = j;
        // cnt[len]++;
    }

    if (pos != -1 && mx == mx2 && cnt[mx] == 2) {
        prt(1);
    } else {
        prt(0);
    }
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
