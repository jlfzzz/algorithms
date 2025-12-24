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

// lazy线段树 + 注意力

const int N = (1e5 + 5) * 4;
pii dxy[4] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

struct Node {
    pii dxy1, dxy2;
    int lazy;
} tree[N];

pii pref[int(5e5 + 5)];
vi temp;

Node pushup(Node a, Node b) {
    Node res;
    res.dxy1 = {a.dxy1.fi + b.dxy1.fi, a.dxy1.se + b.dxy1.se};
    res.dxy2 = {a.dxy2.fi + b.dxy2.fi, a.dxy2.se + b.dxy2.se};
    res.lazy = 0;
    return res;
}

void apply(int o) {
    swap(tree[o].dxy1, tree[o].dxy2);
    tree[o].lazy ^= 1;
}

void pushdown(int o) {
    if (tree[o].lazy) {
        apply(o * 2);
        apply(o * 2 + 1);
        tree[o].lazy = 0;
    }
}

int getId(int x) { return ranges::lower_bound(temp, x) - temp.begin(); }

void build(int o, int l, int r) {
    tree[o].lazy = 0;
    if (l == r) {
        int timeL = temp[l];
        int timeR = temp[l + 1];

        pii valR = (timeR - 1 < 0) ? make_pair(0ll, 0ll) : pref[timeR - 1];
        pii valL = (timeL - 1 < 0) ? make_pair(0ll, 0ll) : pref[timeL - 1];

        tree[o].dxy1 = {valR.fi - valL.fi, valR.se - valL.se};
        tree[o].dxy2 = {0, 0};
        return;
    }

    int m = (l + r) / 2;
    build(o * 2, l, m);
    build(o * 2 + 1, m + 1, r);
    tree[o] = pushup(tree[o * 2], tree[o * 2 + 1]);
}

void update(int o, int l, int r, int ql, int qr) {
    if (r < ql || l > qr)
        return;
    if (l >= ql && r <= qr) {
        apply(o);
        return;
    }

    pushdown(o);
    int m = (l + r) / 2;
    update(o * 2, l, m, ql, qr);
    update(o * 2 + 1, m + 1, r, ql, qr);
    tree[o] = pushup(tree[o * 2], tree[o * 2 + 1]);
}

void solve() {
    int n, t;
    cin >> n >> t;

    vi qs;
    for (int i = 0; i < n; i++) {
        int pos;
        cin >> pos;
        temp.pb(pos);
        qs.pb(pos);
    }

    temp.pb(0);
    temp.pb(t);
    temp.pb(-1);
    ranges::sort(temp);
    temp.erase(unique(all(temp)), temp.end());

    pref[0] = dxy[0];
    F(i, 1, 500'004) {
        pref[i].fi = pref[i - 1].fi + dxy[i % 4].fi;
        pref[i].se = pref[i - 1].se + dxy[i % 4].se;
    }

    int m = temp.size();
    build(1, 1, m - 2);

    for (int pos: qs) {
        int i = getId(pos);
        update(1, 1, m - 2, i, m - 1);
        auto [x, y] = tree[1].dxy1;

        cout << x << " " << y << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
