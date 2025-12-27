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

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> L, R, sz, col;
    int count;

    explicit UnionFind(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);

        L.resize(n);
        R.resize(n);
        sz.resize(n, 1);
        col.resize(n);
        iota(L.begin(), L.end(), 0);
        iota(R.begin(), R.end(), 0);
        iota(col.begin(), col.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return root_x;
        }

        int new_root;
        int child;


        if (rank[root_x] >= rank[root_y]) {
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y])
                rank[root_x]++;
            new_root = root_x;
            child = root_y;
        } else {
            parent[root_x] = root_y;
            new_root = root_y;
            child = root_x;
        }

        sz[new_root] += sz[child];
        L[new_root] = min(L[new_root], L[child]);
        R[new_root] = max(R[new_root], R[child]);

        count--;
        return new_root;
    }
};

void init() {}

void solve() {
    int n, q;
    rd(n, q);

    UnionFind dsu(n + 1);
    vl cnt(n + 1, 1);

    while (q--) {
        int type;
        rd(type);
        if (type == 1) {
            int x, c;
            rd(x, c);

            int root = dsu.find(x);
            int old_c = dsu.col[root];

            if (old_c == c)
                continue;

            cnt[old_c] -= dsu.sz[root];
            cnt[c] += dsu.sz[root];

            dsu.col[root] = c;

            if (dsu.L[root] > 1) {
                int left_neighbor = dsu.L[root] - 1;
                int left_root = dsu.find(left_neighbor);
                if (dsu.col[left_root] == c) {
                    root = dsu.unite(root, left_root);
                }
            }

            if (dsu.R[root] < n) {
                int right_neighbor = dsu.R[root] + 1;
                int right_root = dsu.find(right_neighbor);
                if (dsu.col[right_root] == c) {
                    root = dsu.unite(root, right_root);
                }
            }

        } else {
            int c;
            rd(c);
            prt(cnt[c]);
        }
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
