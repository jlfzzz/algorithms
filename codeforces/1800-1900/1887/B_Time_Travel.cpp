#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace utils {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;

#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int n, t;
    rd(n, t);

    vector<vector<pii>> g(n + 1);

    for (int i: range(1, t + 1)) {
        int m;
        rd(m);
        for (int _i = 0; _i < m; _i++) {
            int u, v;
            rd(u, v);
            g[u].eb(v, i);
            g[v].eb(u, i);
        }
    }

    int k;
    rd(k);

    vector<int> a(k + 1);
    for (int i: range(1, k + 1)) {
        rd(a[i]);
    }

    vector<vector<int>> pos(t + 1);
    for (int i: range(1, k + 1)) {
        pos[a[i]].pb(i);
    }

    vector<int> dist(n + 1, (int) inf);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[1] = 1;
    pq.emplace(1, 1);

    while (!pq.empty()) {
        auto [idx, u] = pq.top();
        pq.pop();
        if (idx != dist[u]) {
            continue;
        }
        if (u == n) {
            prt(max<int>(1, idx - 1));
            return;
        }
        if (idx > k) {
            continue;
        }
        if (idx + 1 < dist[u]) {
            dist[u] = idx + 1;
            pq.emplace(idx + 1, u);
        }
        for (auto &[v, timeId]: g[u]) {
            auto &lst = pos[timeId];
            if (lst.empty()) {
                continue;
            }
            auto it = lower_bound(lst.begin(), lst.end(), idx);
            if (it == lst.end()) {
                continue;
            }
            int t = *it;
            int nid = t + 1;
            if (nid < dist[v]) {
                dist[v] = nid;
                pq.emplace(nid, v);
            }
        }
    }

    prt(-1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
