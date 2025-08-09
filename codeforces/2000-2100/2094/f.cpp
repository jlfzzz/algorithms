#include <bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define PII pair<int, int>
using namespace std;
int t = 1, n, m, k, cnt;
void solve() {
    cin >> n >> m >> k;
    cnt = 1;
    if (m % k != 0) {
        for (int i = 1; i <= n; i++) {
            for (int i = 1; i <= m; i++) {
                cout << cnt << " ";
                if (cnt == k)
                    cnt = 1;
                else
                    cnt++;
            }
            cout << "\n";
        }
    } else {
        for (int i = 1; i <= n; i++) {
            cnt = i;
            if (cnt > k)
                cnt %= k;
            if (cnt == 0)
                cnt = k;
            for (int j = 1; j <= m; j++) {
                cout << cnt << " ";
                if (cnt == k)
                    cnt = 1;
                else
                    cnt++;
            }
            cout << "\n";
        }
    }
}
int main() {
    //	freopen(".in","r",stdin);
    //	freopen(".out","w",stdout);
    cin >> t;
    while (t--) {
        solve();
    }
}
