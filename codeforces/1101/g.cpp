#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
int n, ans, a[N], cnt, d[35];

inline void insert(int x) {
    for (int i = 30; i >= 0; i--) {
        if (x & (1 << i)) {
            if (!d[i]) {
                ++cnt;
                d[i] = x;
                break;
            } else
                x = d[i] ^ x;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), a[i] ^= a[i - 1];
    if (!a[n]) {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        insert(a[i]);
    printf("%d\n", cnt);
    return 0;
}
