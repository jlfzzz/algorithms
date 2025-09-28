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

    template<typename... Args>
    void prt_end(const string &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
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

namespace helpers {
    vector<int> random_array(int n, int lo, int hi) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(lo, hi);

        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }
        return arr;
    }

    // 打印整数的二进制表示 template<typename T>
    template<typename T>
    void prt_bin(T x, int width = -1, char fill = '0') {
        static_assert(is_integral_v<T>, "prt_bin only supports integral types");

        string s;
        if (x == 0) {
            s = "0";
        } else {
            while (x != 0) {
                s.push_back((x & 1) ? '1' : '0');
                x >>= 1;
            }
            reverse(s.begin(), s.end());
        }

        // 如果指定了宽度，则填充
        if (width > 0 && (int) s.size() < width) {
            s = string(width - s.size(), fill) + s;
        }

        cout << s << "\n";
    }

    // 打印向量的二进制
    template<typename T>
    void prt_vec_bin(const vector<T> &v, int width = -1, char fill = '0') {
        for (size_t i = 0; i < v.size(); i++) {
            prt_bin(v[i], width, fill);
        }
    }

} // namespace helpers

using namespace io;
using namespace helpers;

void func1() {
    int n = 10;
    int k = 100;

    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> random_arr = random_array(n, 1, 100);

    prt_bin(5, 5);
}

int main() { func1(); }
