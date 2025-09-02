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

    auto ask = [&](vector<int> &v) -> int {
        cout << "? " << v.size() << ' ';
        for (int x: v) {
            cout << x << ' ';
        }
        cout << endl;
        int t;
        cin >> t;
        return t;
    };

    int l = 1, r = n + 1;
    int pos = -1;
    while (l < r) {
        int m = (l + r) / 2;
        vector<int> v;
        for (int i = 1; i <= m; i++) {
            v.push_back(i);
        }

        int t = ask(v);
        if (t > 0) {
            pos = m;
            r = m;
        } else {
            l = m + 1;
        }
    }

    string ans(n + 1, '?');
    if (pos == -1) {
        l = 2, r = n + 1;
        int target = -1;
        while (l < r) {
            int m = (l + r) / 2;
            vector<int> v;
            v.push_back(m), v.push_back(1);

            int t = ask(v);

            if (t != 0) {
                target = m;
                r = m;
            } else {
                l = m + 1;
            }
        }

        assert(target >= 2);
        for (int i = 1; i < target; i++) {
            ans[i] = ')';
        }
        for (int i = target; i <= n; i++) {
            ans[i] = '(';
        }
    } else {
        int pos1 = pos - 1, pos2 = pos;

        // 确定哪个是 '(' 哪个是 ')'
        vector<int> q;
        q = {pos1, pos2};
        int t12 = ask(q);
        int idxL, idxR; // '(' index, ')' index
        if (t12 > 0) {
            idxL = pos1;
            idxR = pos2;
        } else {
            q = {pos2, pos1};
            int t21 = ask(q);
            assert(t21 > 0);
            idxL = pos2;
            idxR = pos1;
        }
        ans[idxL] = '(';
        ans[idxR] = ')';

        // 批量按 8 位处理，分隔符用已知的 ')': idxR
        vector<int> rem;
        for (int i = 1; i <= n; i++)
            if (i != idxL && i != idxR)
                rem.push_back(i);

        for (int p = 0; p < (int) rem.size(); p += 8) {
            vector<int> vec;
            for (int bit = 0; bit < 8; bit++) {
                int j = p + bit;
                int reps = 1 << bit;
                for (int k = 0; k < reps; k++) {
                    int posq = (j < (int) rem.size()) ? rem[j] : idxL; // 不足时填充无影响的 '('
                    vec.push_back(posq);
                    vec.push_back(idxR);
                    vec.push_back(idxR);
                }
            }
            int res = ask(vec);
            for (int bit = 0; bit < 8; bit++) {
                int j = p + bit;
                if (j >= (int) rem.size())
                    break;
                if ((res >> bit) & 1)
                    ans[rem[j]] = '(';
                else
                    ans[rem[j]] = ')';
            }
        }
    }

    ans = ans.substr(1);
    cout << "! " << ans << endl;
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
