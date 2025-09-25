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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

int K;

struct TrieNode {
    int count{};
    int idx = -1;
    TrieNode *left{}, *right{};
};

struct Trie {
    TrieNode *root;
    Trie() { root = new TrieNode(); }

    void insert(int val, int idx) {
        auto curr = root;
        for (int i = K - 1; i >= 0; i--) {
            int bit = val >> i & 1;
            if (bit == 1) {
                if (curr->right == nullptr) {
                    curr->right = new TrieNode();
                }
                curr = curr->right;
                curr->count++;
            } else {
                if (curr->left == nullptr) {
                    curr->left = new TrieNode();
                }
                curr = curr->left;
                curr->count++;
            }
        }
        curr->idx = idx;
    }

    pii get(int val) {
        auto curr = root;
        int res = 0;
        for (int i = K - 1; i >= 0; i--) {
            int bit = val >> i & 1;
            if (bit == 1) {
                if (curr->right == nullptr) {
                    res += 1 << i;
                    if (curr->left == nullptr) {
                        return {-1, -1};
                    }
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            } else {
                if (curr->left == nullptr) {
                    res += 1 << i;
                    if (curr->right == nullptr) {
                        return {-1, -1};
                    }
                    curr = curr->right;
                } else {
                    curr = curr->left;
                }
            }
        }

        return {res, curr->idx};
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    K = k;

    Trie trie;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int mn = inf;
    pii ans{-1, -1};
    For(i, n) {
        int x = a[i];

        auto [t, idx] = trie.get(x);
        if (idx != -1) {
            if (t < mn) {
                mn = t;
                ans = {idx, i};
            }
        }

        trie.insert(x, i);
    }

    int i1 = a[ans.first], j1 = a[ans.second];
    int x = 0;
    for (int i = k - 1; i >= 0; i--) {
        int b1 = i1 >> i & 1;
        int b2 = j1 >> i & 1;

        if (b1 == b2) {
            if (b1 == 0) {
                x |= 1 << i;
            }
        }
    }

    cout << ans.first + 1 << ' ' << ans.second + 1 << ' ' << x << '\n';
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
