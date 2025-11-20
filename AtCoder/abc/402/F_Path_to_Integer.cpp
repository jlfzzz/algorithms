#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    ll M;
    rd(n, M);

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    F(i, 1, n) {
        F(j, 1, n) { rd(a[i][j]); }
    }

    if (n == 1) {
        cout << (a[1][1] % M) << '\n';
        return;
    }

    vector<vector<i128>> Lvals(n + 1);
    auto dfsL = [&](auto &&self, int x, int y, int steps, i128 cur) -> void {
        cur = cur * 10 + a[x][y];
        if (steps == n - 1) {
            Lvals[x].push_back(cur);
            return;
        }
        if (x + 1 <= n)
            self(self, x + 1, y, steps + 1, cur);
        if (y + 1 <= n)
            self(self, x, y + 1, steps + 1, cur);
    };

    dfsL(dfsL, 1, 1, 0, (i128) 0);

    vector<vector<i128>> Rvals(n + 1);
    auto dfsR = [&](auto &&self, int midRow, int x, int y, i128 cur) -> void {
        cur = cur * 10 + a[x][y];
        if (x == n && y == n) {
            Rvals[midRow].push_back(cur);
            return;
        }
        if (x + 1 <= n)
            self(self, midRow, x + 1, y, cur);
        if (y + 1 <= n)
            self(self, midRow, x, y + 1, cur);
    };

    F(i, 1, n) {
        int j = n + 1 - i;
        if (i + 1 <= n)
            dfsR(dfsR, i, i + 1, j, (i128) 0);
        if (j + 1 <= n)
            dfsR(dfsR, i, i, j + 1, (i128) 0);
    }

    ll tenPow = 1 % M;
    for (int k = 0; k < n - 1; ++k) {
        tenPow = (tenPow * 10) % M;
    }

    ll ans = 0;
    F(i, 1, n) {
        if (Lvals[i].empty() || Rvals[i].empty())
            continue;

        vector<ll> qmod;
        qmod.reserve(Rvals[i].size());
        for (i128 q: Rvals[i]) {
            ll qm = (ll) (q % M);
            if (qm < 0)
                qm += M;
            qmod.push_back(qm);
        }
        sort(all(qmod));
        qmod.erase(unique(all(qmod)), qmod.end());

        for (i128 p: Lvals[i]) {
            ll pm = (ll) (p % M);
            if (pm < 0)
                pm += M;
            ll base = (ll) (((__int128) pm * tenPow) % M);
            ll limit = M - 1 - base;

            auto it = upper_bound(all(qmod), limit);
            if (it != qmod.begin()) {
                --it;
                ll cand = (base + *it) % M;
                if (cand > ans)
                    ans = cand;
            }
            ll qmax = qmod.back();
            ll cand2 = (base + qmax) % M;
            if (cand2 > ans)
                ans = cand2;
        }
    }

    cout << ans << '\n';
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
