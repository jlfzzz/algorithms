#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
// #define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

struct TrieNode {
    int nxt[2];
    int count;
};

struct Trie {
    static const int MAXBIT = 30;
    vector<TrieNode> pool;
    int root, pool_ptr;

    Trie(int max_nodes = 0) {
        pool.resize(max_nodes);
        root = 0;
        pool_ptr = 1;
        pool[0].nxt[0] = pool[0].nxt[1] = -1;
        pool[0].count = 0;
    }

    inline int newNode() {
        int id = pool_ptr++;
        pool[id].nxt[0] = pool[id].nxt[1] = -1;
        pool[id].count = 0;
        return id;
    }

    void clear() {
        pool_ptr = 1;
        pool[0].nxt[0] = pool[0].nxt[1] = -1;
        pool[0].count = 0;
    }

    void insert(int x) {
        int cur = root;
        pool[cur].count++;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (pool[cur].nxt[bit] == -1) {
                pool[cur].nxt[bit] = newNode();
            }
            cur = pool[cur].nxt[bit];
            pool[cur].count++;
        }
    }

    int get_max(int x) {
        int cur = root;
        int ans = 0;
        if (pool[cur].count == 0)
            return ans;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int t = 1 - bit;
            if (pool[cur].nxt[t] != -1 && pool[pool[cur].nxt[t]].count > 0) {
                ans |= (1 << i);
                cur = pool[cur].nxt[t];
            } else if (pool[cur].nxt[bit] != -1 && pool[pool[cur].nxt[bit]].count > 0) {
                cur = pool[cur].nxt[bit];
            }
        }
        return ans;
    }

    void erase(int x) {
        int cur = root;
        pool[cur].count--;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            cur = pool[cur].nxt[bit];
            pool[cur].count--;
        }
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    Trie trie((n + 5) * 32);

    int l = 0;
    int ans = n + 1;
    for (int r = 0; r < n; r++) {
        int x = a[r];
        trie.insert(x);
        int mx = trie.get_max(x);

        while (mx >= k && l <= r) {
            ans = min(ans, r - l + 1);
            trie.erase(a[l]);
            l++;
            mx = trie.get_max(x);
        }
    }

    cout << (ans == n + 1 ? -1 : ans) << '\n';
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
