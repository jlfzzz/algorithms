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
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

#include <cmath>
#include <iostream>
#include <set>
#include <vector>


using namespace std;

// Sieve of Eratosthenes
vector<int> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}

int main() {
    long long L, R;
    cin >> L >> R;

    // L=R 的情况，区间 [L+1, R] 为空
    if (L == R) {
        cout << 1 << endl;
        return 0;
    }

    long long l = L + 1;
    long long r = R;

    // 1. 基础筛法，筛到 sqrt(r)
    int max_sieve = sqrt(r);
    vector<int> primes = sieve(max_sieve);

    long long count_primes = 0;
    long long count_powers = 0;

    // 2. 区间筛 (Segmented Sieve) 统计 k=1 的质数
    // is_prime_segment[i] 对应数字 l+i
    vector<bool> is_prime_segment(r - l + 1, true);

    for (long long p: primes) {
        // 找到 p 在 [l, r] 中的第一个倍数，但至少从 p*p 开始
        long long start = (l + p - 1) / p * p;
        if (start < p * p) {
            start = p * p;
        }

        for (long long j = start; j <= r; j += p) {
            if (j >= l) {
                is_prime_segment[j - l] = false;
            }
        }
    }

    for (int i = 0; i < is_prime_segment.size(); ++i) {
        if (is_prime_segment[i]) {
            count_primes++;
        }
    }

    // 3. 统计 k >= 2 的质数幂
    set<long long> found_powers;
    for (long long p: primes) {
        long long n = p;
        // 循环检查 n*p 是否会溢出或超过 r
        while (r / p >= n) {
            n = n * p; // n = p^2, p^3, ...
            if (n >= l) {
                found_powers.insert(n);
            }
        }
    }
    count_powers = found_powers.size();

    // 4. 最终答案
    // 1 (来自 A_L) + 区间内的质数 + 区间内的质数幂(k>=2)
    cout << 1 + count_primes + count_powers << endl;

    return 0;
}

