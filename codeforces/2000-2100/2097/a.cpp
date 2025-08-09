#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        map<int, int> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i], m[a[i]]++;
        sort(a + 1, a + n + 1);
        bool flag = false, vis = false;
        for (int i = 1; i <= n; i++) {
            if (m[a[i]] >= 4) {
                cout << "Yes" << '\n';
                flag = true;
                break;
            }
            if (a[i] - a[i - 1] >= 2)
                vis = false;
            if (vis && m[a[i]] >= 2 && a[i] == a[i - 1] + 1) {
                cout << "Yes" << '\n';
                flag = true;
                break;
            }
            if (!(vis && m[a[i]] >= 1 && a[i] == a[i - 1] + 1))
                vis = false;
            if (m[a[i]] >= 2)
                vis = true;
        }
        if (!flag)
            cout << "No" << '\n';
    }
    return 0;
}
