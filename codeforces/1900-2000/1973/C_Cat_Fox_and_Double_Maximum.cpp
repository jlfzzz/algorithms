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
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    int pos = find(p.begin(), p.end(), n) - p.begin();

    bool rev = false;
    if (pos % 2 == 0) {
        reverse(p.begin(), p.end());
        rev = true;
    }

    vector<int> ans(n);

    vector<pii> odd, even;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 1)
            odd.emplace_back(p[i], i);
        else
            even.emplace_back(p[i], i);
    }

    sort(odd.begin(), odd.end());
    for (int i = 0; i < odd.size(); i++) {
        ans[odd[i].second] = n - i;
    }

    sort(even.begin(), even.end(), greater<>());
    for (int i = 0; i < even.size(); i++) {
        ans[even[i].second] = i + 1;
    }

    if (rev)
        reverse(ans.begin(), ans.end());

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
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
