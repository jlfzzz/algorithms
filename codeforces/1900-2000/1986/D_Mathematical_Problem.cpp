#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
void solve() {
    cin >> n >> s;
    if (n == 2) {
        cout << (s[0] - '0') * 10 + s[1] - '0' << "\n";
    } else if (n > 3 && s.find("0") != -1) {
        cout << "0\n";
    } else if (n == 3 && (s[0] == '0' || s[2] == '0')) {
        cout << "0\n";
    } else {
        int res = 1e18;
        for (int i = 0; i < n - 1; i++) {
            int ans = 0, lst = 1;
            for (int j = 0; j < n; j++) {
                int c = s[j] - '0';
                if (j == i + 1) {
                    continue;
                }
                if (j == i) { // 找到断点
                    c = c * 10 + s[j + 1] - '0';
                }
                if (c == 1) { // 字符为 1，跳过
                    continue;
                }
                if (lst != 1)
                    ans += lst; // 累加答案
                lst = c;
            }
            res = min(res, ans + lst);
        }
        cout << res << "\n";
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
/*
311312
3*1+1*3+12 = 18
3+11+3*1+2 = 19

901
*/
