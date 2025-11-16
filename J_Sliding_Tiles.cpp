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
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
const char nl = '\n';

void dbg() { cerr << "\n"; }

template<typename T, typename... Args>
void dbg(const string &s, T x, Args... args) {
    cerr << s << " = " << x;
    if (sizeof...(args) > 0) {
        cerr << ", ";
    }
    dbg(args...);
}

struct Seg {
    int n;
    vector<int> mn, mx, lazy;
    Seg(int m) {
        n = m;
        mn.assign(4 * n + 5, 0);
        mx.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }
    void pushdown(int x, int s, int e) {
        if (lazy[x] == 0 || s == e) {
            return;
        }
        int v = lazy[x];
        int lc = x * 2, rc = x * 2 + 1;
        mn[lc] += v;
        mx[lc] += v;
        lazy[lc] += v;
        mn[rc] += v;
        mx[rc] += v;
        lazy[rc] += v;
        lazy[x] = 0;
    }
    void rangeAdd(int x, int s, int e, int L, int R, int val) {
        if (R < s || e < L || L > R) {
            return;
        }
        if (L <= s && e <= R) {
            mn[x] += val;
            mx[x] += val;
            lazy[x] += val;
            return;
        }
        pushdown(x, s, e);
        int m = (s + e) / 2;
        rangeAdd(x * 2, s, m, L, R, val);
        rangeAdd(x * 2 + 1, m + 1, e, L, R, val);
        mn[x] = min(mn[x * 2], mn[x * 2 + 1]);
        mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
    }
    int getVal(int x, int s, int e, int pos) {
        if (s == e) {
            return mn[x];
        }
        pushdown(x, s, e);
        int m = (s + e) / 2;
        if (pos <= m) {
            return getVal(x * 2, s, m, pos);
        } else {
            return getVal(x * 2 + 1, m + 1, e, pos);
        }
    }
    int getMaxRightEqual(int x, int s, int e, int st, int val) {
        if (e < st) {
            return e;
        }
        if (mn[x] == val && mx[x] == val) {
            return e;
        }
        if (s == e) {
            return s - 1;
        }
        pushdown(x, s, e);
        int m = (s + e) / 2;
        int leftPos = getMaxRightEqual(x * 2, s, m, st, val);
        if (leftPos < m) {
            return leftPos;
        }
        return getMaxRightEqual(x * 2 + 1, m + 1, e, st, val);
    }
};

struct Fenwick {
    int n;
    vector<long long> tr;
    Fenwick(int m) {
        n = m + 4;
        tr.assign(n + 5, 0);
    }
    void add(int pos, long long val) {
        pos++;
        for (int i = pos; i < n; i += i & -i) {
            tr[i] += val;
        }
    }
    long long get(int pos) {
        pos++;
        long long res = 0;
        for (int i = pos; i > 0; i -= i & -i) {
            res += tr[i];
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> h(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> h[i];
    }
    h[n - 1] = n;

    Seg tr(n);
    Fenwick fen(n + 4);

    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            tr.rangeAdd(1, 0, n - 1, 0, a[i] - 1, 1);
        }
        if (h[i] > 0) {
            int pos = 0;
            while (pos < h[i]) {
                int stval = tr.getVal(1, 0, n - 1, pos);
                int rpos = min(h[i] - 1, tr.getMaxRightEqual(1, 0, n - 1, pos, stval));
                if (stval != 0) {
                    tr.rangeAdd(1, 0, n - 1, pos, rpos, -stval);
                    fen.add(i - stval + 1, rpos - pos + 1);
                    fen.add(i + 1, -(rpos - pos + 1));
                }
                pos = rpos + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << fen.get(i) << (i + 1 == n ? "" : " ");
    }
    cout << nl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
