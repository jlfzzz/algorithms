#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
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
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    ll N;
    long long M;
    rd(N, M);
    vl P(N);
    rv(P);

    auto check = [&](i128 X) -> pair<i128, i128> {
        i128 total_cost = 0;
        i128 total_count = 0;

        for (i128 p: P) {
            if (X < p)
                continue;

            // 计算该商品买多少个
            i128 k = (X / p + 1) / 2;

            if (k > 0) {
                // 【核心修复 1】：预判 k 是否大到离谱
                // M 最大 10^18。如果 k > 2*10^9，则 k*k > 4*10^18，肯定买不起。
                // 这样避免了 k*k 之后甚至可能连 i128 都会溢出的极端情况（当 N 很大时）。
                if (k > 2000000000LL) {
                    return {(i128) M + 7, 0}; // 返回一个大于 M 的值即可
                }

                // 计算这一项的花费
                i128 term = k * k * p;

                // 【核心修复 2】：累加前检查，或者累加后立即检查
                // 为了防止 total_cost 累加到爆 i128，我们一旦发现它超过 M 就停。
                if (term > M || total_cost + term > M) {
                    return {(i128) M + 7, 0}; // 已经买不起了，返回 > M
                }

                total_cost += term;
                total_count += k;
            }
        }
        return {total_cost, total_count};
    };

    i128 L = 0, R = 2000000000000000000LL;
    i128 best_X = 0;

    while (L <= R) {
        i128 mid = L + (R - L) / 2;
        pair<i128, i128> res = check(mid);

        if (res.first <= M) {
            best_X = mid;
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }

    // 重新计算 best_X 的确切花费和数量
    // 因为 best_X 是合法的，所以 check(best_X) 肯定不会触发上面的 > M 返回逻辑
    pair<i128, i128> res = check(best_X);
    i128 final_count = res.second;
    i128 money_used = res.first;
    i128 rem_money = M - money_used;

    if (rem_money > 0) {
        final_count += rem_money / (best_X + 1);
    }

    prt((long long) final_count);
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
