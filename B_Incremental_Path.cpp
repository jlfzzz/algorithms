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
    string s;
    cin >> s;
    vector<int> a(m);
    For(i, m) cin >> a[i];

    int pos = 1;
    set<int> st;
    for (int x: a)
        st.insert(x);

    map<int, int> nx;
    auto get = [&](this auto &&get, int x) -> int {
        auto it = nx.find(x);
        if (it == nx.end())
            return x;
        return it->second = get(it->second);
    };

    for (int x: a)
        nx[x] = get(x + 1);

    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            pos++;
            if (!st.contains(pos)) {
                st.insert(pos);
                nx[pos] = get(pos + 1);
            }
        } else {
            int y = get(pos + 1);
            st.insert(y);
            nx[y] = get(y + 1);
            pos = get(y + 1);
        }
    }

    cout << st.size() << '\n';
    for (int x: st)
        cout << x << ' ';
    cout << '\n';
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
