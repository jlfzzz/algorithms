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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    multiset<int> st;
    int total = 0;

    for (int i = 0; i < n; i++) {
        string s = to_string(a[i]);
        total += s.size();
        int c0 = 0;
        for (int j = s.size() - 1; j >= 0; j--) {
            if (s[j] != '0') {
                break;
            } else {
                c0++;
            }
        }
        st.insert(c0);
    }

    int cnt = 0;
    int f = 0;
    while (!st.empty()) {
        if (f) {
            if (st.size() < 2) {
                break;
            } else {
                int x = *prev(st.end());
                st.erase(prev(st.end()));
                int y = *prev(st.end());
                st.erase(prev(st.end()));
                st.insert(min(x, y));
            }
        } else {
            int x = *prev(st.end());
            st.erase(prev(st.end()));

            cnt += x;
            st.insert(0);
        }
        f ^= 1;
    }

    cout << (total - cnt > m ? "Sasha\n" : "Anna\n");
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
