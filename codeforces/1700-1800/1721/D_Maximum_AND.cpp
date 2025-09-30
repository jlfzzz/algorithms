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

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
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

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
} // namespace io

using namespace io;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n), b(n);
    rd_vec(a);
    rd_vec(b);

    int ans = 0;
    vector<int> idA(n, 0), idB(n, 0);
    for (int bit = 29; bit >= 0; bit--) {
        map<int, pii> need, have;
        for (int i = 0; i < n; i++) {
            if (a[i] >> bit & 1)
                need[idA[i]].second++;
            else
                need[idA[i]].first++;
        }
        for (int i = 0; i < n; i++) {
            if (b[i] >> bit & 1)
                have[idB[i]].second++;
            else
                have[idB[i]].first++;
        }

        bool ok = true;
        for (auto &[gid, cnt]: need) {
            pii temp = have[gid];
            if (!(temp.first == cnt.second && temp.second == cnt.first)) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;

        ans |= (1 << bit);

        vector<int> nidA(n), nidB(n);
        int cur_id = 0;
        map<pii, int> mp;
        for (int i = 0; i < n; i++) {
            int old = idA[i];
            int val = (a[i] >> bit) & 1;
            pii key = {old, val};
            if (!mp.count(key))
                mp[key] = cur_id++;
            nidA[i] = mp[key];
        }
        for (int i = 0; i < n; i++) {
            int old = idB[i];
            int val = 1 - ((b[i] >> bit) & 1);
            pii key = {old, val};
            nidB[i] = mp[key];
        }
        idA.swap(nidA);
        idB.swap(nidB);
    }

    prt(ans);
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
