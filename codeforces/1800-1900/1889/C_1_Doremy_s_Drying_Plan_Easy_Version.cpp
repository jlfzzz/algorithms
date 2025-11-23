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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, m, k;
    rd(n, m, k);

    vector<pii> segs(m);
    for (int i = 0; i < m; ++i)
        rd(segs[i].first, segs[i].second);

    vector<int> diff(n + 2, 0);
    for (auto [l, r]: segs) {
        diff[l]++;
        diff[r + 1]--;
    }

    vector<int> cnt(n + 1);
    int zero_cnt = 0;
    int cur = 0;
    F(i, 1, n) {
        cur += diff[i];
        cnt[i] = cur;
        if (cnt[i] == 0)
            zero_cnt++;
    }

    vector<int> pref1(n + 1, 0), pref2(n + 1, 0);
    F(i, 1, n) {
        pref1[i] = pref1[i - 1] + (cnt[i] == 1);
        pref2[i] = pref2[i - 1] + (cnt[i] == 2);
    }

    vector<int> one(m);
    for (int i = 0; i < m; i++) {
        int l = segs[i].first;
        int r = segs[i].second;
        one[i] = pref1[r] - pref1[l - 1];
    }

    vector<int> one2 = one;
    sort(all(one2), greater<int>());
    int ans = zero_cnt + one2[0] + one2[1];

    vector<vector<int>> add_at(n + 2), remove_at(n + 2);
    for (int i = 0; i < m; i++) {
        add_at[segs[i].first].pb(i);
        remove_at[segs[i].second + 1].pb(i);
    }

    set<int> active;
    map<pii, int> overlap_len;

    F(i, 1, n) {
        for (int id: add_at[i])
            active.insert(id);
        for (int id: remove_at[i])
            active.erase(id);

        if (cnt[i] == 2) {
            int u = *active.begin();
            int v = *active.rbegin();
            overlap_len[{u, v}]++;
        }
    }

    for (auto const &[pair_ids, len]: overlap_len) {
        int u = pair_ids.first;
        int v = pair_ids.second;

        int current_gain = zero_cnt + one[u] + one[v] + len;
        ans = max(ans, current_gain);
    }

    prt(ans);
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
