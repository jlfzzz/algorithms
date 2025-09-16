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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    {
        bool f = false;
        for (int x: a) {
            if (x == 0) {
                f = true;
            }
        }
        if (!f) {
            cout << n << '\n';
            return;
        }
    }

    int p0 = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            p0 = i;
            break;
        }
    }

    map<int, int> suf;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] != 0) {
            suf[a[i]]++;
        }
    }
    suf[0]++;

    int mex = 0;
    while (suf.contains(mex)) {
        mex++;
    }

    bool f = true;
    int mn = inf;
    for (int i = 0; i < p0; i++) {
        int x = a[i];
        mn = min(mn, x);
        suf[x]--;
        if (suf[x] == 0) {
            suf.erase(x);
            if (x < mex)
                mex = x;
        }

        if (mn < mex) {
            f = false;
            break;
        }
    }


    int c0 = 0;
    for (int x: a) {
        if (x == 0) {
            c0++;
        }
    }
    int ans = 1;

    if (f) {
        ans = n - c0 + 1;
    } else {
        ans = n - c0;
    }

    cout << ans << '\n';

    // vector<int> zeros;
    // for (int i = 0; i < n; i++) {
    //     if (a[i] == 0) {
    //         zeros.push_back(i);
    //     }
    // }
    // int c0 = zeros.size();

    // set<int> cnt;
    // {
    //     int i = n - 1;
    //     while (i >= 0 && a[i] != 0) {
    //         cnt.insert(a[i]);
    //         i--;
    //     }
    // }

    // int mex = 1;
    // while (cnt.contains(mex)) {
    //     mex++;
    // }

    // for (int i = zeros.size() - 1; i >= 0; i--) {
    //     int zero = zeros[i];
    //     int left = (i - 1 >= 0) ? zeros[i - 1] : -1;

    //     bool f = true;
    //     int j = zero - 1;
    //     while (j > left) {
    //         int y = a[j];
    //         if (y < mex) {
    //             f = false;
    //         }
    //         if (y == mex) {
    //             mex++;
    //             while (cnt.contains(mex)) {
    //                 mex++;
    //             }
    //         }
    //         cnt.insert(y);
    //         j--;
    //     }

    //     if (f) {
    //         cout << n - c0 + 1 << '\n';
    //         return;
    //     }
    // }

    // cout << n - c0 << '\n';
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
