#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n);
    vector<int> b(m);
    For(i, n) cin >> a[i];
    For(i, m) cin >> b[i];

    unordered_map<int, int> order;
    unordered_map<int, int> order_to_val;
    for (int i = 0; i < n; i++) {
        order[a[i]] = i;
        order_to_val[i] = a[i];
    }

    vector<set<int>> cnt(n);
    for (int i = 0; i < m; i++) {
        cnt[order[b[i]]].insert(i);
    }

    auto check = [&](int i) -> bool {
        // int curr = order[b[i]], pre = (i - 1 >= 0) ? order[b[i - 1]] : -1, nxt = (i + 1 < n) ? order[b[i + 1]] : n;
        int curr = i, pre = (i - 1 >= 0) ? i - 1 : -1, nxt = (i + 1 < n) ? i + 1 : n;
        int pre_first = (pre == -1 || cnt[pre].empty()) ? -1 : *cnt[pre].begin();
        int nxt_first = (nxt == n || cnt[nxt].empty()) ? inf : *cnt[nxt].begin();

        // cout << "i is" << i << ' ' << "pre,curr,nxt are" << pre_first << ' ' << curr << ' ' << nxt_first << endl;

        if (cnt[curr].empty()) {
            return pre_first < nxt_first;
        } else {
            int curr_first = *cnt[curr].begin();
            return curr_first > pre_first && curr_first < nxt_first;
        }
    };

    // 初始化 matches
    int matches = 0;
    for (int i = 0; i < n; i++)
        matches += check(i);

    // 初始输出
    cout << ((b[0] == a[0] && matches == n) ? "YA\n" : "TIDAK\n");

    For(_, q) {
        int s, t;
        cin >> s >> t;
        --s;
        int old_val = b[s];
        if (old_val == t) {
            cout << ((b[0] == a[0] && matches == n) ? "YA\n" : "TIDAK\n");
            continue;
        }
        int i1 = order[old_val], i2 = order[t];

        // 收集受影响的 rank 索引
        vector<int> idxs = {i1 - 1, i1, i1 + 1, i2 - 1, i2, i2 + 1};
        idxs.erase(remove_if(idxs.begin(), idxs.end(), [&](int x) { return x < 0 || x >= n; }), idxs.end());
        sort(idxs.begin(), idxs.end());
        idxs.erase(unique(idxs.begin(), idxs.end()), idxs.end());

        // 扣除旧贡献
        int sub = 0;
        for (int idx: idxs)
            sub += check(idx);

        // 真正更新
        cnt[i1].erase(s);
        cnt[i2].insert(s);
        b[s] = t;

        // 加上新贡献
        int add = 0;
        for (int idx: idxs)
            add += check(idx);

        matches += (add - sub);

        cout << ((b[0] == a[0] && matches == n) ? "YA\n" : "TIDAK\n");
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
