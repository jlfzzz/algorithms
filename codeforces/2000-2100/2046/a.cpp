#include <bits/stdc++.h>
using namespace std;
long long ans, n, a[5005][2];
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i][1];
        for (int i = 1; i <= n; i++)
            cin >> a[i][2]; // 注意读入方式
        ans = -2e9;
        for (int i = 1; i <= n; i++) { // 设 i 为向下走的点并枚举
            long long sum = a[i][1] + a[i][2];
            for (int j = 1; j <= n; j++)
                if (i != j)
                    sum += max(a[j][1], a[j][2]);
            ans = max(ans, sum);
        }
        cout << ans << endl;
    }
    return 0;
}
