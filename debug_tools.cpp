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

namespace math {
    // 质因数分解
    vector<int> decompose(int x) {
        vector<int> primes;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                primes.push_back(i);
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        if (x > 1) {
            primes.push_back(x);
        }
        return primes;
    }
} // namespace math

using namespace io;
using namespace helpers;
using namespace math;

void func1() {
    int n = 10000;

    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> random_arr = random_array(n, 1, 1e9);

    // random_arr = {5, 10};
    prt_vec(random_arr);

    n = random_arr.size();

    ll mx = 0;
    pii mx_p{-1, -1};
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        int xors = 0;
        for (int j = i; j < n; j++) {
            sum += random_arr[j];
            xors ^= random_arr[j];
            if (mx_p.first == -1) {
                mx = sum - xors;
                mx_p = {i, j};
            } else if (sum - xors >= mx) {
                if (j - i < mx_p.second - mx_p.first) {
                    mx = sum - xors;
                    mx_p = {i, j};
                }
            }
        }
    }

    ll sum = accumulate(random_arr.begin(), random_arr.end(), 0ll);
    prt("sum is", sum);

    sum = 0;
    for (int x: random_arr) {
        sum ^= x;
    }
    prt("xors is", sum);

    prt(mx_p.first + 1, mx_p.second + 1);
    prt("mx is:", mx);
}

int main() { func1(); }
