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
    string s;
    cin >> n >> s;
    s = " " + s;
    int cntl = 0, cnti = 0, cntt = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] == 'L')
            cntl++;
        else if (s[i] == 'I')
            cnti++;
        else if (s[i] == 'T')
            cntt++;
    if (cntl == n || cnti == n || cntt == n) {
        cout << -1 << endl;
        return;
    }

    vector<int> ans;
    int leftl = n - cntl, lefti = n - cnti, leftt = n - cntt;
    // cerr << leftl << " " << lefti << " " << leftt << endl;

    while (1) {
        if (!leftl && !lefti && !leftt) {
            cout << ans.size() << endl;
            for (int i: ans)
                cout << i << endl;
            return;
        }

        for (int i = 1; i < n; ++i) {
            if (!leftl)
                break;
            if ((s[i] == 'I' && s[i + 1] == 'T') || (s[i] == 'T' && s[i + 1] == 'I')) {
                leftl--, s.insert(s.begin() + i + 1, 'L'), n++, ans.push_back(i);
                // cerr << i << " " << s << endl;
            }
        }

        for (int i = 1; i < n; ++i) {
            if (!lefti)
                break;
            if ((s[i] == 'L' && s[i + 1] == 'T') || (s[i] == 'T' && s[i + 1] == 'L')) {
                lefti--, s.insert(s.begin() + i + 1, 'I'), n++, ans.push_back(i);
                // cerr << i << " " << s << endl;
            }
        }
        for (int i = 1; i < n; ++i) {
            if (!leftt)
                break;
            if ((s[i] == 'I' && s[i + 1] == 'L') || (s[i] == 'L' && s[i + 1] == 'I')) {
                leftt--, s.insert(s.begin() + i + 1, 'T'), n++, ans.push_back(i);
                // cerr << i << " " << s << endl;
            }
        }
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
