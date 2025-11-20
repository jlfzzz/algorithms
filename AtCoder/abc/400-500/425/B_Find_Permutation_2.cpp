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

    int cnt = 0;
    set<int> st;
    For(i, n) {
        int x = a[i];
        if (x == -1) {
            continue;
        }
        if (x > n) {
            cout << "No\n";
            return;
        }
        if (st.contains(x)) {
            cout << "No\n";
            return;
        }

        st.insert(x);
    }

    vector<int> temp;
    for (int i = 1; i <= n; i++) {
        if (!st.contains(i)) {
            temp.push_back(i);
        }
    }

    int j = 0;
    For(i, n) {
        if (a[i] != -1) {
            continue;
        }
        a[i] = temp[j];
        j++;
    }

    cout << "Yes\n";
    for (int x: a)
        cout << x << ' ';
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
