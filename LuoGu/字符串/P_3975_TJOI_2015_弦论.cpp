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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

template<int SIGMA = 26, char MIN_CHAR = 'a'>
struct SuffixAutomaton {
    struct State {
        int next[SIGMA];
        int link;
        int len;

        State(int _len = 0, int _link = -1) : link(_link), len(_len) { fill(next, next + SIGMA, -1); }
    };

    vector<State> st; // states
    vector<long long> occ; // endpos count for each state (after prepare_occurrences)
    int last; // id of the state corresponding to the whole string

    SuffixAutomaton(int max_len = 0) { init(max_len); }

    // 重新初始化，max_len 为要插入的字符串的最大长度（用于 reserve）
    void init(int max_len = 0) {
        st.clear();
        occ.clear();
        st.reserve(2 * max_len + 1);
        occ.reserve(2 * max_len + 1);

        st.emplace_back(0, -1);
        occ.push_back(0);
        last = 0;
    }

    // 插入一个字符
    void extend(char ch) {
        int c = ch - MIN_CHAR;
        if (c < 0 || c >= SIGMA) {
            assert(false && "character out of alphabet range");
        }

        int cur = (int) st.size();
        st.emplace_back(st[last].len + 1, 0);
        occ.push_back(1); // 新状态对应一个新的 endpos
        int p = last;

        for (; p != -1 && st[p].next[c] == -1; p = st[p].link) {
            st[p].next[c] = cur;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int) st.size();
                st.push_back(st[q]);
                occ.push_back(0);
                st[clone].len = st[p].len + 1;

                for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = clone;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // 用整串一次性建 SAM
    void build(const string &s) {
        if ((int) st.size() == 0) {
            init((int) s.size());
        }
        for (char ch: s)
            extend(ch);
    }

    // 判断 pattern 是否是原串的一个子串
    bool contains_substring(const string &pattern) const {
        int v = 0;
        for (char ch: pattern) {
            int c = ch - MIN_CHAR;
            if (c < 0 || c >= SIGMA)
                return false;
            if (st[v].next[c] == -1)
                return false;
            v = st[v].next[c];
        }
        return true;
    }

    // 准备各状态 endpos 出现次数（把次数沿 suffix link 往上推）
    void prepare_occurrences() {
        int sz = (int) st.size();
        int max_len = 0;
        for (int i = 0; i < sz; ++i)
            max_len = max(max_len, st[i].len);

        vector<int> cnt(max_len + 1);
        for (int i = 0; i < sz; ++i)
            cnt[st[i].len]++;
        for (int i = 1; i <= max_len; ++i)
            cnt[i] += cnt[i - 1];

        vector<int> order(sz);
        for (int i = sz - 1; i >= 0; --i) {
            order[--cnt[st[i].len]] = i;
        }

        for (int i = sz - 1; i > 0; --i) {
            int v = order[i];
            int p = st[v].link;
            if (p >= 0)
                occ[p] += occ[v];
        }
    }

    // 不同子串个数
    long long count_distinct_substrings() const {
        long long res = 0;
        int sz = (int) st.size();
        for (int v = 1; v < sz; ++v) {
            int link = st[v].link;
            res += (long long) (st[v].len - (link == -1 ? 0 : st[link].len));
        }
        return res;
    }

    // 与另一个串 t 的最长公共子串长度
    int longest_common_substring(const string &t) const {
        int v = 0;
        int l = 0;
        int best = 0;

        for (char ch: t) {
            int c = ch - MIN_CHAR;
            if (c < 0 || c >= SIGMA) {
                v = 0;
                l = 0;
                continue;
            }

            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                ++l;
            } else {
                while (v != -1 && st[v].next[c] == -1) {
                    v = st[v].link;
                }
                if (v == -1) {
                    v = 0;
                    l = 0;
                    continue;
                } else {
                    l = st[v].len + 1;
                    v = st[v].next[c];
                }
            }
            best = max(best, l);
        }
        return best;
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    string s;
    rd(s);
    int t;
    ll k;
    rd(t, k);

    SuffixAutomaton<> sam((int) s.size());
    sam.build(s);
    if (t == 1) {
        sam.prepare_occurrences();
    }

    int sz = (int) sam.st.size();
    vector<int> order(sz);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) { return sam.st[a].len > sam.st[b].len; });

    vector<ll> dp(sz);
    for (int idx = 0; idx < sz; idx++) {
        int v = order[idx];
        dp[v] = 0;
        for (int c = 0; c < 26; c++) {
            int u = sam.st[v].next[c];
            if (u == -1) {
                continue;
            }
            if (t == 0) {
                dp[v] += 1 + dp[u];
            } else {
                dp[v] += sam.occ[u] + dp[u];
            }
        }
    }

    ll total = dp[0];
    if (k > total) {
        prt("-1");
        return;
    }

    string ans;
    int v = 0;
    while (true) {
        for (int c = 0; c < 26; c++) {
            int u = sam.st[v].next[c];
            if (u == -1) {
                continue;
            }
            ll cnt_here = (t == 0 ? 1LL : sam.occ[u]);
            ll block = cnt_here + dp[u];
            if (k > block) {
                k -= block;
                continue;
            }
            ans.push_back((char) ('a' + c));
            if (k <= cnt_here) {
                prt(ans);
                return;
            }
            k -= cnt_here;
            v = u;
            break;
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
