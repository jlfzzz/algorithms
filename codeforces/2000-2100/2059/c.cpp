#include <bits/stdc++.h>
using namespace std;
const int N = 3e2 + 5;

int a[N][N];

void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 0; j--) {
            if (a[i][j] != 1) {
                v[i] = n - j;
                break;
            }
        }
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] > ans)
            ans++;
    }
    cout << min(ans + 1, n) << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
