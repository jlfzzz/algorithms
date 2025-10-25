#include <bits/stdc++.h>
using namespace std;

namespace io {
    inline ostream &operator<<(ostream &os, __int128_t value) {
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

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
constexpr int MOD = int(1e9 + 7);
using ll = long long;


class Solution {
public:
    int getMaximumNumber(vector<vector<int>> &moles) {
        ranges::sort(moles, [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
        vector<vector<int>> dp(3, vector<int>(3, -1));
        dp[1][1] = 0;

        int n = moles.size(), pre = 0, idx = 0;

        while (idx < n) {
            int t = moles[idx][0];
            int dt = t - pre;

            vector<pair<int, int>> cur;
            while (idx < n && moles[idx][0] == t) {
                cur.emplace_back(moles[idx][1], moles[idx][2]);
                idx++;
            }

            vector<vector<int>> ndp(3, vector<int>(3, -1));
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (dp[i][j] == -1)
                        continue;
                    for (int dx = 0; dx < 3; dx++) {
                        for (int dy = 0; dy < 3; dy++) {
                            if (abs(i - dx) + abs(j - dy) <= dt) {
                                ndp[dx][dy] = max(ndp[dx][dy], dp[i][j]);
                            }
                        }
                    }
                }
            }

            for (auto &[x, y]: cur) {
                if (ndp[x][y] != -1) {
                    ndp[x][y]++;
                }
            }

            dp = std::move(ndp);
            pre = t;
        }

        int ans = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
