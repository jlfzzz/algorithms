#include <bits/stdc++.h>
// #pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
const int N = 505;
int n, m, a[N][N], b[N][N];
string s;
void work() {
    // 输入
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        cin >> s;
        for (int j = 1; j <= m; j++) {
            a[i][j] = s[j - 1] - '0';
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> s;
        for (int j = 1; j <= m; j++) {
            b[i][j] = s[j - 1] - '0';
        }
    }
    // 判断是否存在某行或某列值之和不相等的情况
    int suma, sumb;
    for (int i = 1; i <= n; i++) {
        suma = sumb = 0;
        for (int j = 1; j <= m; j++) {
            suma = (suma + a[i][j]) % 3;
            sumb = (sumb + b[i][j]) % 3;
        }
        // 若不相等
        if (suma != sumb) {
            printf("NO\n");
            return;
        }
    }
    for (int i = 1; i <= m; i++) {
        suma = sumb = 0;
        for (int j = 1; j <= n; j++) {
            suma = (suma + a[j][i]) % 3;
            sumb = (sumb + b[j][i]) % 3;
        }
        // 若不相等
        if (suma != sumb) {
            printf("NO\n");
            return;
        }
    }
    // 不存在不相等的情况
    printf("YES\n");
}
int main() {
    //  ios::sync_with_stdio(false);
    //  cin.tie(0),cout.tie(0);
    // 多组数据
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
