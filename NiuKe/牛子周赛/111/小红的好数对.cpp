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

int pow10[15];

void init() {
    pow10[0] = 1;
    for (int i = 1; i < 15; i++) {
        pow10[i] = 10 * pow10[i - 1];
    }
}

void solve() {
    int n;
    read(n);
    vector<int> a(n);
    read_vec(a);

    auto f = [&](vector<int> &arr) -> int {
        int res = 0;

        vector<int> temp(n);
        For(i, n) { temp[i] = arr[i] % 11; }

        map<int, int> cnt;
        vector<int> mask(n);
        For(i, n) {
            int x = arr[i];
            int len = to_string(x).size();
            int cur = 0;
            for (int j = 0; j <= 10; j++) {
                int t = x + j * pow10[len];
                if (t % 11 == 0) {
                    cur |= 1 << j;
                }
            }
            mask[i] = cur;
        }

        For(i, n) {
            int x = arr[i];
            int cur = mask[i];
            for (int j = 0; j <= 10; j++) {
                if (cur >> j & 1) {
                    res += cnt[j];
                }
            }
            cnt[x % 11]++;
        }
        return res;
    };

    int ans = f(a);
    ranges::reverse(a);
    ans += f(a);
    prt(ans);
}

void solve2() {
    int n;
    read(n);
    vector<int> a(n);
    read_vec(a);

    int c[2][11] = {};
    for (int v: a) {
        int parity = to_string(v).size() & 1;
        c[parity][v % 11] += 1;
    }

    int ans = 0;
    for (int i = 0; i < 11; i++) {
        ans += (c[0][i] + c[1][i]) * c[1][i];
        ans += (c[0][i] + c[1][i]) * c[0][(11 - i) % 11];
    }
    int s = 0;
    for (int i = 0; i < 11; i++)
        s += c[1][i];
    ans -= s;
    ans -= c[0][0];
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
        solve2();
    return 0;
}
