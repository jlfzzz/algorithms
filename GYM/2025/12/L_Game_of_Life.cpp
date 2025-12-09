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

constexpr int N = 1e6 + 5;

int Multitest = 0;

using Mat = vvi;
Mat mat0(10, vi(10));
int n, k;
int M;

void init() {}

Mat matMul(Mat &mat1, Mat &mat2) {
    int n = mat1.size();
    int m = mat1[0].size();
    int p = mat2[0].size();

    Mat res(n, vi(p));

    F(i, 0, n - 1) {
        F(j, 0, p - 1) {
            F(k, 0, m - 1) { res[i][j] ^= (mat1[i][k] & mat2[k][j]); }
        }
    }

    return res;
}

Mat matPow(Mat &mat, int k) {
    int n = mat.size();
    Mat res(n, vi(n));
    F(i, 0, n - 1) { res[i][i] = 1; }

    while (k) {
        if (k & 1) {
            res = matMul(res, mat);
        }
        mat = matMul(mat, mat);
        k /= 2;
    }

    return res;
}

void solve() {
    rd(n, k);

    M = n * n;

    F(i, 0, n - 1) {
        string s;
        rd(s);
        F(j, 0, n - 1) {
            if (s[j] == '#') {
                mat0[i][j] = -1;
            } else {
                mat0[i][j] = s[j] - '0';
            }
        }
    }

    Mat col(1, vi(M));
    F(i, 0, n - 1) {
        F(j, 0, n - 1) {
            if (mat0[i][j] == 1) {
                col[0][i * n + j] = 1;
            }
        }
    }

    Mat mat(M, vi(M));
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    F(r, 0, n - 1) {
        F(c, 0, n - 1) {
            int u = r * n + c;

            if (mat0[r][c] == -1)
                continue;

            mat[u][u] = 1;

            F(d, 0, 7) {
                int nr = r + dx[d];
                int nc = c + dy[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && mat0[nr][nc] != -1) {
                    int v = nr * n + nc;
                    mat[v][u] = 1;
                }
            }
        }
    }

    Mat mat1 = matPow(mat, k);

    Mat ans = matMul(col, mat1);

    F(i, 0, n - 1) {
        F(j, 0, n - 1) {
            if (mat0[i][j] == -1) {
                cout << '#';
            } else {
                cout << ans[0][i * n + j];
            }
        }
        cout << '\n';
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
