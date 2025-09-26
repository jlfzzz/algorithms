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
    int n, d;
    cin >> n >> d;
    string s;
    cin >> s;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = s[i] - '0';

    string ans;
    int u = 1 << n;
    for (int mask = 1; mask < u; mask++) {
        vector<int> temp;
        for (int j = 0; j < n; j++)
            if (mask & (1 << j))
                temp.push_back(arr[j]);

        sort(temp.begin(), temp.end());
        do {
            string s;
            for (int digit: temp)
                s += ('0' + digit);

            int mod = 0;
            for (char c: s)
                mod = (mod * 10 + (c - '0')) % d;

            if (mod == 0) {
                if (ans == "" || s.size() < ans.size() || (s.size() == ans.size() && s < ans))
                    ans = s;
            }
        } while (next_permutation(temp.begin(), temp.end()));
    }

    if (ans == "")
        cout << -1 << '\n';
    else {
        int i = 0;
        while (i < ans.size() - 1 && ans[i] == '0')
            i++;
        cout << ans.substr(i) << '\n';
    }
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
