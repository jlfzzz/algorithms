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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
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

#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int N, T;
    rd(N, T);

    struct Mat {
        int a[4][4]{};
    };

    auto I4 = [&]() {
        Mat M;
        M.a[0][0] = 1;
        M.a[1][1] = 1;
        M.a[2][2] = 1;
        M.a[3][3] = 1;
        return M;
    };

    auto mul = [&](const Mat &A, const Mat &B) {
        Mat C;
        for (int i = 0; i < 4; i++) {
            for (int k = 0; k < 4; k++)
                if (A.a[i][k] != 0) {
                    for (int j = 0; j < 4; j++)
                        if (B.a[k][j] != 0) {
                            C.a[i][j] += A.a[i][k] * B.a[k][j];
                        }
                }
        }
        return C;
    };

    auto mat_for_run = [&](int len, bool activeR) {
        // Build 4x4 from blocks using C^len and I - C^len
        int m = ((len % 4) + 4) % 4;
        int Ck[2][2];
        if (m == 0) {
            Ck[0][0] = 1;
            Ck[0][1] = 0;
            Ck[1][0] = 0;
            Ck[1][1] = 1;
        } else if (m == 1) {
            Ck[0][0] = 0;
            Ck[0][1] = 1;
            Ck[1][0] = -1;
            Ck[1][1] = 0;
        } else if (m == 2) {
            Ck[0][0] = -1;
            Ck[0][1] = 0;
            Ck[1][0] = 0;
            Ck[1][1] = -1;
        } else {
            Ck[0][0] = 0;
            Ck[0][1] = -1;
            Ck[1][0] = 1;
            Ck[1][1] = 0;
        }
        int I2[2][2] = {{1, 0}, {0, 1}};
        int ImC[2][2] = {{I2[0][0] - Ck[0][0], I2[0][1] - Ck[0][1]}, {I2[1][0] - Ck[1][0], I2[1][1] - Ck[1][1]}};
        Mat M;
        auto put2 = [&](int r, int c, int v) { M.a[r][c] = v; };
        if (activeR) {
            // [ Ck,  I-Ck;  0,  I ]
            put2(0, 0, Ck[0][0]);
            put2(0, 1, Ck[0][1]);
            put2(1, 0, Ck[1][0]);
            put2(1, 1, Ck[1][1]);
            put2(0, 2, ImC[0][0]);
            put2(0, 3, ImC[0][1]);
            put2(1, 2, ImC[1][0]);
            put2(1, 3, ImC[1][1]);
            put2(2, 0, 0);
            put2(2, 1, 0);
            put2(3, 0, 0);
            put2(3, 1, 0);
            put2(2, 2, 1);
            put2(2, 3, 0);
            put2(3, 2, 0);
            put2(3, 3, 1);
        } else {
            // [ I,  0;  I-Ck,  Ck ]
            put2(0, 0, 1);
            put2(0, 1, 0);
            put2(1, 0, 0);
            put2(1, 1, 1);
            put2(0, 2, 0);
            put2(0, 3, 0);
            put2(1, 2, 0);
            put2(1, 3, 0);
            put2(2, 0, ImC[0][0]);
            put2(2, 1, ImC[0][1]);
            put2(3, 0, ImC[1][0]);
            put2(3, 1, ImC[1][1]);
            put2(2, 2, Ck[0][0]);
            put2(2, 3, Ck[0][1]);
            put2(3, 2, Ck[1][0]);
            put2(3, 3, Ck[1][1]);
        }
        return M;
    };

    struct Stats {
        int cnt; // number of runs
        Mat eff0, eff1; // product when starting parity at leftmost run is 0 or 1
    };

    auto combineStats = [&](const Stats &A, const Stats &B) {
        // total = B then A (time concatenation)
        Stats C;
        C.cnt = A.cnt + B.cnt;
        bool even = (A.cnt % 2 == 0);
        const Mat &B0 = even ? B.eff0 : B.eff1;
        const Mat &B1 = even ? B.eff1 : B.eff0;
        C.eff0 = mul(B0, A.eff0);
        C.eff1 = mul(B1, A.eff1);
        return C;
    };

    struct Node {
        int len; // length of this run in seconds
        int sum; // total seconds in subtree
        int cnt; // runs in subtree
        Mat leaf0, leaf1; // for this run only
        Mat eff0, eff1; // for subtree
        bool flip; // lazy: toggle starting parity for entire subtree
        unsigned pri;
        Node *l, *r;
        explicit Node(int _len, unsigned _pri) :
            len(_len), sum(_len), cnt(1), flip(false), pri(_pri), l(nullptr), r(nullptr) {}
    };

    std::mt19937 rng((unsigned) chrono::steady_clock::now().time_since_epoch().count());

    auto build_leaf = [&](int len) {
        Node *u = new Node(len, rng());
        u->leaf0 = mat_for_run(len, true);
        u->leaf1 = mat_for_run(len, false);
        u->eff0 = u->leaf0;
        u->eff1 = u->leaf1;
        return u;
    };

    auto applyFlip = [&](Node *u) {
        if (!u)
            return;
        swap(u->eff0, u->eff1);
        u->flip = !u->flip;
    };

    function<void(Node *)> push = [&](Node *u) {
        if (!u || !u->flip)
            return;
        applyFlip(u->l);
        applyFlip(u->r);
        u->flip = false;
    };

    function<void(Node *)> pull = [&](Node *u) {
        u->sum = u->len;
        u->cnt = 1;
        if (u->l) {
            u->sum += u->l->sum;
            u->cnt += u->l->cnt;
        }
        if (u->r) {
            u->sum += u->r->sum;
            u->cnt += u->r->cnt;
        }

        Stats leftS;
        leftS.cnt = 0;
        leftS.eff0 = I4();
        leftS.eff1 = I4();
        Stats midS;
        midS.cnt = 1;
        midS.eff0 = u->leaf0;
        midS.eff1 = u->leaf1;
        Stats rightS;
        rightS.cnt = 0;
        rightS.eff0 = I4();
        rightS.eff1 = I4();
        if (u->l) {
            leftS.cnt = u->l->cnt;
            leftS.eff0 = u->l->eff0;
            leftS.eff1 = u->l->eff1;
        }
        if (u->r) {
            rightS.cnt = u->r->cnt;
            rightS.eff0 = u->r->eff0;
            rightS.eff1 = u->r->eff1;
        }

        Stats lm = leftS.cnt ? combineStats(leftS, midS) : midS;
        Stats lmr = rightS.cnt ? combineStats(lm, rightS) : lm;
        u->eff0 = lmr.eff0;
        u->eff1 = lmr.eff1;
    };

    function<pair<Node *, Node *>(Node *, int)> splitBySeconds = [&](Node *u,
                                                                     int needLeftSeconds) -> pair<Node *, Node *> {
        if (!u)
            return {nullptr, nullptr};
        push(u);
        int leftSeconds = u->l ? u->l->sum : 0;
        if (needLeftSeconds < leftSeconds) {
            auto pr = splitBySeconds(u->l, needLeftSeconds);
            u->l = pr.second;
            pull(u);
            return {pr.first, u};
        }
        if (needLeftSeconds > leftSeconds + u->len) {
            auto pr = splitBySeconds(u->r, needLeftSeconds - leftSeconds - u->len);
            u->r = pr.first;
            pull(u);
            return {u, pr.second};
        }
        // split inside this node: left part length = max(0, needLeftSeconds - leftSeconds)
        int leftLen = max<int>(0, needLeftSeconds - leftSeconds);
        int rightLen = u->len - leftLen;

        Node *L = u->l;
        Node *R = u->r;

        Node *leftNode = nullptr, *rightNode = nullptr;
        if (leftLen > 0) {
            leftNode = build_leaf(leftLen);
        }
        if (rightLen > 0) {
            rightNode = build_leaf(rightLen);
        }

        // We discard u and rebuild two sides: merge(L, leftNode) and merge(rightNode, R)
        function<Node *(Node *, Node *)> merge = [&](Node *a, Node *b) -> Node * {
            if (!a)
                return b;
            if (!b)
                return a;
            if (a->pri < b->pri) {
                push(a);
                a->r = merge(a->r, b);
                pull(a);
                return a;
            } else {
                push(b);
                b->l = merge(a, b->l);
                pull(b);
                return b;
            }
        };

        Node *leftTree = merge(L, leftNode);
        Node *rightTree = merge(rightNode, R);
        return {leftTree, rightTree};
    };

    function<Node *(Node *, Node *)> merge = [&](Node *a, Node *b) -> Node * {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->pri < b->pri) {
            push(a);
            a->r = merge(a->r, b);
            pull(a);
            return a;
        } else {
            push(b);
            b->l = merge(a, b->l);
            pull(b);
            return b;
        }
    };

    // removed unused helper

    Node *root = build_leaf(T);

    for (int i = 0; i < N; i++) {
        int b;
        rd(b);
        auto pr = splitBySeconds(root, (int) b);
        Node *L = pr.first, *R = pr.second;
        if (R)
            applyFlip(R);
        root = merge(L, R);
        // Final product starting parity 0
        const Mat &P = root->eff0;
        cout << P.a[0][2] << ' ' << P.a[1][2] << '\n';
    }
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
