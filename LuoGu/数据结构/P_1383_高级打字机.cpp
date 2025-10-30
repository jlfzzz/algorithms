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
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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

using namespace utils;

constexpr int N = 1e5 + 5;

int Multitest = 0;

void init() {}

struct Node {
    char c;
    int cnt;
} tree[25 * N];

int ls[25 * N];
int rs[25 * N];

int tot;
int root[N];
int len[N];
int idForMod[N];
int modCnt;

void pushup(int o) { tree[o].cnt = tree[ls[o]].cnt + tree[rs[o]].cnt; }

int change(int pre, int l, int r, int pos, char c) {
    int cur = ++tot;
    tree[cur] = tree[pre];
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];

    if (l == r) {
        tree[cur].c = c;
        tree[cur].cnt = 1;
        return cur;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid)
        ls[cur] = change(ls[pre], l, mid, pos, c);
    else
        rs[cur] = change(rs[pre], mid + 1, r, pos, c);
    pushup(cur);
    return cur;
}

char query(int o, int l, int r, int k) {
    if (l == r) {
        return tree[o].c;
    }
    int mid = (l + r) >> 1;
    if (tree[ls[o]].cnt >= k) {
        return query(ls[o], l, mid, k);
    }
    return query(rs[o], mid + 1, r, k - tree[ls[o]].cnt);
}

void solve() {
    tot = 0;
    modCnt = 0;

    int n;
    rd(n);
    root[0] = 0;
    len[0] = 0;

    F(i, 1, n) {
        char op;
        rd(op);

        if (op == 'T') {
            char x;
            rd(x);
            int pre = root[i - 1];
            int pos = len[i - 1] + 1;
            root[i] = change(pre, 1, N, pos, x);
            len[i] = pos;
            idForMod[++modCnt] = i;
        } else if (op == 'U') {
            int x;
            rd(x);
            int k = modCnt - x;
            if (k <= 0) {
                root[i] = root[0];
                len[i] = len[0];
            } else {
                int idx = idForMod[k];
                root[i] = root[idx];
                len[i] = len[idx];
            }
            idForMod[++modCnt] = i;
        } else if (op == 'Q') {
            int x;
            rd(x);
            root[i] = root[i - 1];
            len[i] = len[i - 1];
            prt(query(root[i], 1, N, x));
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
