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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    s = ' ' + s;

    set<int> st;
    for (int i = n; i >= 1; i--) {
        if (s[i] == '1') {
            st.insert(i);
        } else {
            ans += i;
            if (!st.empty()) {
                int last = *st.rbegin();
                st.erase(last);
            }
        }
    }

    while (!st.empty()) {
        int x = *st.begin();
        st.erase(x);
        if (!st.empty()) {
            int last = *st.rbegin();
            st.erase(last);
        }
        ans += x;
    }

    cout << ans << '\n';
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
