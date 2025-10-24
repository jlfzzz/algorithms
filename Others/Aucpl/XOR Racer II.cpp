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

// https://aucpl.com/problem/xorracerii

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
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
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

struct TrieNode {
    int count;
    array<unique_ptr<TrieNode>, 2> nxt;

    TrieNode() : count(0), nxt{nullptr, nullptr} {}
};

struct Trie {
    unique_ptr<TrieNode> root;

    Trie() : root(make_unique<TrieNode>()) {}

    void insert(int x) const {
        TrieNode *curr = root.get();
        curr->count++;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!curr->nxt[bit]) {
                curr->nxt[bit] = make_unique<TrieNode>();
            }
            curr = curr->nxt[bit].get();
            curr->count++;
        }
    }

    int get_max(int x) const {
        TrieNode *curr = root.get();
        int ans = 0;
        if (!curr || curr->count == 0)
            return ans;

        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int t = 1 - bit;
            if (curr->nxt[t] && curr->nxt[t]->count > 0) {
                ans |= (1 << i);
                curr = curr->nxt[t].get();
            } else if (curr->nxt[bit] && curr->nxt[bit]->count > 0) {
                curr = curr->nxt[bit].get();
            } else {
                break;
            }
        }
        return ans;
    }

    int get_min(int x) const {
        TrieNode *curr = root.get();
        int ans = 0;
        if (!curr || curr->count == 0)
            return ans;

        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (curr->nxt[bit] && curr->nxt[bit]->count > 0) {
                curr = curr->nxt[bit].get();
            } else if (curr->nxt[1 - bit] && curr->nxt[1 - bit]->count > 0) {
                ans |= (1 << i);
                curr = curr->nxt[1 - bit].get();
            } else {
                break;
            }
        }
        return ans;
    }

    void erase(int x) const {
        TrieNode *curr = root.get();
        curr->count--;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            curr = curr->nxt[bit].get();
            curr->count--;
        }
    }
};

#define int ll

int Multitest = 0;

void solve() {
    int n, q;
    rd(n, q);

    vector<vector<pii>> g(n + 1);
    for (int _: range(q)) {
        int u, v, c;
        rd(u, v, c);
        g[u].eb(v, c);
        g[v].eb(u, c);
    }

    vector<int> vis(n + 1);
    int ans = 0;
    for (int i: range(1, n + 1)) {
        if (vis[i]) {
            continue;
        }

        Trie trie;
        trie.insert(0);
        int mx = 0;
        auto dfs = [&](auto &&dfs, int u, int fa, int sum) -> void {
            vis[u] = 1;
            for (auto [v, w]: g[u]) {
                if (v == fa) {
                    continue;
                }

                int t = sum ^ w;
                trie.insert(t);
                mx = max<int>({trie.get_max(t), mx, w});
                dfs(dfs, v, u, t);
            }
        };

        dfs(dfs, i, 0, 0);
        ans += mx;
    }

    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    if (Multitest)
        rd(T);
    while (T--)
        solve();
    return 0;
}
