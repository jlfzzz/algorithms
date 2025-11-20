#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
ll a[N], n, k;
int main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    sort(a, a + n);
    if (k >= n) {
        puts("0");
        return 0;
    }
    ll res = 0;
    for (int i = 0; i < n - 1; i++)
        a[i] = a[i + 1] - a[i];
    sort(a, a + n - 1);
    for (int i = 0; i < n - k; i++)
        res += a[i];
    printf("%lld", res);
    return 0;
}
