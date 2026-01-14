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
#define us unsigned
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

ll cnt1[50'005], cnt2[50'005];

void solve() {
    int n;
    rd(n);

    vl a(n + 1);
    rv(a, 1);

    int q;
    rd(q);

    const int B = int(n / sqrt(q * 2 / 3 + 1)) + 1;

    struct Q {
        int l, r, id, sign;
    };

    vector<Q> queries;
    for (int i = 0; i < q; i++) {
        int l1, r1, l2, r2;
        rd(l1, r1, l2, r2);

        queries.pb(r1, r2, i, 1);
        if (l1 - 1 >= 1 && l2 - 1 >= 1) {
            queries.pb(l1 - 1, l2 - 1, i, 1);
        }

        if (l1 - 1 >= 1) {
            queries.pb(l1 - 1, r2, i, -1);
        }

        if (l2 - 1 >= 1) {
            queries.pb(r1, l2 - 1, i, -1);
        }
    }

    sort(queries.begin(), queries.end(), [&](Q &a, Q &b) {
        int l1 = a.l / B;
        int l2 = b.l / B;
        if (l1 != l2)
            return a.l < b.l;
        return (l1 & 1) ? (a.r < b.r) : (a.r > b.r);
    });

    ll sum = 0;

    auto addL = [&](int pos) {
        int val = a[pos];
        sum += cnt2[val];
        cnt1[val]++;
    };
    auto delL = [&](int pos) {
        int val = a[pos];
        cnt1[val]--;
        sum -= cnt2[val];
    };

    auto addR = [&](int pos) {
        int val = a[pos];
        sum += cnt1[val];
        cnt2[val]++;
    };
    auto delR = [&](int pos) {
        int val = a[pos];
        cnt2[val]--;
        sum -= cnt1[val];
    };

    int curL = 0, curR = 0;
    vector<ll> ans(q);

    for (auto &[l, r, id, sign]: queries) {
        while (curL < l)
            addL(++curL);
        while (curL > l)
            delL(curL--);

        while (curR < r)
            addR(++curR);
        while (curR > r)
            delR(curR--);

        ans[id] += 1ll * sign * sum;
    }

    for (ll x: ans) {
        prt(x);
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
