#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define ld long double
#define db double
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

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

int Multitest = 1;

void init() {}

constexpr int NEG = 1e9 + 5;


void solve() {
    int n, m;
    rd(n, m);

    string s, t;
    rd(s, t);

    string s1 = " " + t;
    string s2 = " " + s;
    s1 += " ";

    int N = m;
    int M = n;

    vector<vector<short>> dp_pre(N + 2, vector<short>(M + 2, 0));
    vector<vector<short>> dp_suf(N + 2, vector<short>(M + 2, 0));
    vector<vector<short>> ok_pre(N + 2, vector<short>(M + 2, 0));
    vector<vector<short>> ok_suf(N + 2, vector<short>(M + 2, 0));
    vector<vector<short>> cursor_pos(N + 2, vector<short>(M + 2, 0));

    ok_pre[0][0] = 1;
    cursor_pos[0][0] = 0;
    for (int i: range(0, N + 1)) {
        for (int j: range(1, M + 1)) {
            if (s1[i] == s2[j]) {
                dp_pre[i][j] = dp_pre[i - 1][j - 1];
                ok_pre[i][j] = ok_pre[i - 1][j - 1] & 1;
                cursor_pos[i][j] = cursor_pos[i - 1][j - 1];
            } else {
                dp_pre[i][j] = dp_pre[i][j - 1] + (short) (j - cursor_pos[i][j - 1] + 1);
                cursor_pos[i][j] = (short) j;
                ok_pre[i][j] = ok_pre[i][j - 1];
            }
        }
    }

    for (int i: range(0, N + 2)) {
        for (int j: range(0, M + 2))
            cursor_pos[i][j] = 0;
    }

    ok_suf[N + 1][M + 1] = 1;
    cursor_pos[N + 1][M + 1] = (short) (M + 1);
    for (int i: range(N + 1, 0, -1)) {
        for (int j: range(M, 0, -1)) {
            if (s1[i] == s2[j]) {
                dp_suf[i][j] = dp_suf[i + 1][j + 1];
                ok_suf[i][j] = ok_suf[i + 1][j + 1] & 1;
                cursor_pos[i][j] = cursor_pos[i + 1][j + 1];
            } else {
                dp_suf[i][j] = dp_suf[i][j + 1] + (short) (cursor_pos[i][j + 1] - j);
                cursor_pos[i][j] = (short) j;
                ok_suf[i][j] = ok_suf[i][j + 1];
            }
        }
    }

    short ans = (short) 32767;
    for (int i: range(0, N + 1)) {
        for (int j: range(0, M + 1)) {
            if (ok_pre[i][j] && ok_suf[i + 1][j + 1]) {
                short tag = (i != j) ? (short) 1 : (short) 0;
                short cand = (short) (dp_pre[i][j] + dp_suf[i + 1][j + 1] + tag);
                if (cand < ans)
                    ans = cand;
            }
        }
    }

    if (ans == (short) 32767)
        ans = (short) -1;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
