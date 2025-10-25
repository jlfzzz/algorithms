#include <bits/stdc++.h> //万能头
using namespace std;

int t, n, x, ans;

int main() {
    cin >> t;
    while (t--) {
        ans = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> x;
            ans ^= x;
        }
        if (ans) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
