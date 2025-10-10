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
    long long maxProduct(vector<int> &nums) {
        int mx = ranges::max(nums);

        int m = bit_width((unsigned) mx);
        int u = 1 << m;
        vector<int> dp(u);

        for (int x: nums) {
            dp[x] = x;
        }

        for (int bit = 0; bit < m; bit++) {
            for (int mask = 0; mask < u; mask++) {
                if (!(mask >> bit & 1)) {
                    dp[mask | (1 << bit)] = max(dp[mask | (1 << bit)], dp[mask]);
                }
            }
        }

        long long ans = 0;
        int mask = u - 1;
        for (int x: nums) {
            int t = x ^ mask;
            ans = max(ans, 1ll * x * dp[t]);
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
