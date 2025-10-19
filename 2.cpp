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

#define int ll
int Multitest = 0;

void solve() {
    int n;
    rd(n);
    string s;
    rd(s);

    int co = 0, ch = 0, cb = 0;
    for (char c: s) {
        if (c == 'o')
            co++;
        else if (c == 'b')
            cb++;
        else if (c == 'H')
            ch++;
    }

    if (co == 0 || cb == 0 || ch > 1) {
        cout << -1 << '\n';
        return;
    }

    int ans = 0;
    vector<int> vis(n + 1);
    s = '#' + s;

    int pH = -1;
    for (int i: range(1, n + 1)) {
        if (s[i] == 'H') {
            pH = i;
            break;
        }
    }

    if (pH != -1) {
        vis[1] = 1;
        ans = abs(pH - 1);
    }

    vector<int> posT, tgtT;
    for (int i: range(1, n + 1))
        if (s[i] == 'T')
            posT.pb(i);
    for (int i: range(3, n + 1, 3))
        tgtT.pb(i);

    if (posT.size() != tgtT.size()) {
        cout << -1 << '\n';
        return;
    }

    sort(all(posT));
    sort(all(tgtT));
    for (int i = 0; i < posT.size(); i++) {
        ans += abs(posT[i] - tgtT[i]);
        vis[tgtT[i]] = 1;
    }

    set<int> cB;
    for (int i: range(1, n + 1))
        if (s[i] == 'b')
            cB.insert(i);

    for (int x: cB) {
        int best = -1, bestDist = inf;
        for (int i: range(2, n)) {
            if (!vis[i]) {
                int d = abs(x - i);
                if (d < bestDist) {
                    bestDist = d;
                    best = i;
                }
            }
        }
        if (best == -1) {
            cout << -1 << '\n';
            return;
        }
        ans += bestDist;
        vis[best] = 1;
    }

    vector<int> pos_o, tgt_o;
    for (int i: range(1, n + 1))
        if (s[i] == 'o')
            pos_o.pb(i);
    for (int i: range(1, n + 1))
        if (!vis[i])
            tgt_o.pb(i);

    if (pos_o.size() != tgt_o.size()) {
        cout << -1 << '\n';
        return;
    }
    sort(all(pos_o));
    sort(all(tgt_o));
    for (int i = 0; i < pos_o.size(); i++)
        ans += abs(pos_o[i] - tgt_o[i]);

    cout << ans << '\n';
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
