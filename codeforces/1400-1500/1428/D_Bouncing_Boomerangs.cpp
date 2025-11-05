#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

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
} // namespace utils

using namespace utils;

int Multitest = 0;
int N, A[100003];

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    vector<int> pot;
    for (int i = N; i; --i)
        if (A[i] == 1)
            pot.push_back(i);
    vector<pair<int, int>> ans;
    int col = 1, p;
    for (int i = 1; i <= N; ++i)
        switch (A[i]) {
            case 1:
                if (pot.size() && pot.back() == i) {
                    pot.pop_back();
                    ans.push_back(make_pair(col++, i));
                }
                break;
            case 2:
                if (pot.empty()) {
                    cout << -1;
                    return 0;
                } else {
                    int t = pot.back();
                    pot.pop_back();
                    ans.push_back(make_pair(col, i));
                    ans.push_back(make_pair(col++, t));
                }
                break;
            case 3:
                p = i + 1;
                while (p <= N && (!A[p] || A[p] == 1 && (pot.empty() || pot.back() != p)))
                    ++p;
                if (p > N) {
                    cout << -1;
                    return 0;
                }
                ans.push_back(make_pair(col, i));
                ans.push_back(make_pair(col++, p));
        }
    cout << ans.size() << endl;
    for (auto t: ans)
        cout << t.first << ' ' << t.second << endl;
    return 0;
}
void init() {}

// void solve() {
//     int n;
//     rd(n);
//     vi a(n + 1);
//     rv(a, 1);

//     int c1 = 0, c2 = 0, c3 = 0;
//     D(i, n, 1) {
//         if (a[i] == 1) {
//             c1++;
//         } else if (a[i] == 2) {
//             if (!c1) {
//                 prt(-1);
//                 return;
//             }
//             c1--;
//             c2++;
//         } else if (a[i] == 3) {
//             if (c3) {
//                 continue;
//             }

//             if (c2) {
//                 c2--;
//             } else if (c1) {
//                 c1--;
//             } else {
//                 prt(-1);
//                 return;
//             }
//             c3++;
//         }
//     }

//     vi rows(n + 1);
//     vp ans;

//     int last3 = -1, lasty = -1;
//     {
//         int up = n;
//         bool first = true;
//         F(i, 1, n) {
//             if (a[i] == 3) {
//                 if (first) {
//                     ans.pb(i, up);
//                     lasty = up;
//                     first = false;
//                 } else {
//                     ans.pb(i, up);
//                     ans.pb(i, up - 1);
//                     up--;
//                     lasty = up;
//                 }
//                 last3 = i;
//             }
//         }
//     }

//     vi vis(n + 1);
//     int down = 1;
//     set<pii> ones;
//     D(i, n, 1) {
//         if (a[i] == 1) {
//             ans.pb(i, down);
//             ones.insert({i, down});
//             down++;
//         } else if (a[i] == 2) {
//             auto [j, y] = *ones.begin();
//             ones.erase({j, y});
//             ans.pb(i, y);
//             vis[i] = 1;
//         }
//     }

//     if (last3 != -1) {
//         D(i, n, last3 + 1) {
//             if (a[i] == 1 && !vis[i]) {
//                 auto it = ones.lower_bound({i, -1});

//                 ones.erase(it);
//                 auto [j, y] = *it;
//                 assert(lasty > y);
//                 ans.pb(j, lasty);
//                 break;
//             }
//         }
//     }

//     while (!ones.empty()) {
//         auto [i, y] = *ones.begin();
//         ones.erase(ones.begin());
//         ans.pb(i, y);
//     }

//     prt(ans.size());
//     for (auto [x, y]: ans) {
//         prt(n - y + 1, x);
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     init();
//     int T = 1;
//     if (Multitest) {
//         rd(T);
//     }
//     while (T--) {
//         solve();
//     }
// }
