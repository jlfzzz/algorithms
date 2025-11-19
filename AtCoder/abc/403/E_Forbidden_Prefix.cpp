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

const int MAXN = 5e5 + 10;
const int SIGMA = 26;

struct Trie {
    int son[MAXN][SIGMA];
    int cnt[MAXN];
    int end[MAXN];
    int tot;

    Trie() { init(); }

    void init() {
        tot = 0;
        memset(son[0], 0, sizeof(son[0]));
        cnt[0] = 0;
        end[0] = 0;
    }

    int new_node() {
        ++tot;
        memset(son[tot], 0, sizeof(son[tot]));
        cnt[tot] = 0;
        end[tot] = 0;
        return tot;
    }

    void insert(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                son[p][u] = new_node();
            p = son[p][u];
            cnt[p]++;
        }
        end[p]++;
    }

    bool query1(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                return false;
            p = son[p][u];
            if (end[p]) {
                return true;
            }
        }
        return false;
    }

    int query2(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                return 0;
            p = son[p][u];
        }
        return cnt[p];
    }

    void clear_subtree(int root) {
        static int st[MAXN];
        int top = 0;
        st[top++] = root;
        while (top) {
            int v = st[--top];
            cnt[v] = 0;
            end[v] = 0;
            for (int i = 0; i < SIGMA; i++) {
                int nxt = son[v][i];
                if (nxt) {
                    st[top++] = nxt;
                }
            }
        }
    }

    int erase_prefix(const string &s) {
        int p = 0;
        static int path[MAXN];
        int len = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                return 0;
            p = son[p][u];
            path[len++] = p;
        }
        int val = cnt[p];
        if (!val) {
            return 0;
        }
        for (int i = 0; i < len; i++) {
            cnt[path[i]] -= val;
        }
        clear_subtree(p);
        return val;
    }
};

void init() {}

void solve() {
    int q;
    rd(q);

    static Trie trie1, trie2;
    trie1.init();
    trie2.init();
    int sum = 0;

    while (q--) {
        int op;
        string s;
        rd(op, s);

        if (op == 1) {
            int t = trie2.erase_prefix(s);
            if (t) {
                sum -= t;
            }
            trie1.insert(s);
        } else {
            bool f = trie1.query1(s);
            if (!f) {
                trie2.insert(s);
                sum++;
            }
        }

        prt(sum);
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
