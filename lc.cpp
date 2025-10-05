#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

namespace io {
    inline ostream &operator<<(ostream &os, i128 value) {
        if (value == 0) {
            os << 0;
            return os;
        }
        bool is_negative = value < 0;
        if (is_negative)
            value = -value;
        string digits;
        while (value > 0) {
            int digit = value % 10;
            digits.push_back(char('0' + digit));
            value /= 10;
        }
        if (is_negative)
            os << '-';
        for (int i = digits.size() - 1; i >= 0; --i)
            os << digits[i];
        return os;
    }

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
        for (int i = start_index; i < v.size(); i++) {
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
        for (int i = start_index; i < v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

class Solution {
public:
    long long countNoZeroPairs(long long n) {
        string s = to_string(n);
        vector<int> d;
        for (int i = s.size() - 1; i >= 0; i--)
            d.push_back(s[i] - '0');
        int m = d.size();

        ll dp[17][2][16];
        bool vis[17][2][16] = {{{false}}};

        auto dfs = [&](this auto &&dfs, int i, int carry, int a, int b, int aHas, int bHas) -> ll {
            if (i == m) {
                return (carry == 0 && aHas && bHas) ? 1 : 0;
            }

            int state = (a << 3) | (aHas << 2) | (b << 1) | bHas;

            ll &x = dp[i][carry][state];
            if (vis[i][carry][state])
                return x;
            vis[i][carry][state] = true;

            ll res = 0;
            int need = d[i];

            for (int j = 0; j <= 9; j++) {
                if (a && j != 0)
                    continue;
                int na = a || (j == 0);
                int naHas = aHas || (j > 0);

                for (int k = 0; k <= 9; k++) {
                    if (b && k != 0)
                        continue;
                    int nb = b || (k == 0);
                    int nbHas = bHas || (k > 0);

                    int sum = j + k + carry;
                    if (sum % 10 != need)
                        continue;

                    int ncarry = sum / 10;
                    res += dfs(i + 1, ncarry, na, nb, naHas, nbHas);
                }
            }
            return x = res;
        };

        return dfs(0, 0, 0, 0, 0, 0);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    prt(sol1.countNoZeroPairs(n));
}
