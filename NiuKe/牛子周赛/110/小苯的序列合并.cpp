#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> v(N);
        for (int i = 0; i < N; i++)
            cin >> v[i];

        vector<long long> pre(N + 1, 0);
        for (int i = 0; i < N; i++)
            pre[i + 1] = pre[i] ^ v[i];

        int ans = 0;
        for (int i = 29; i >= 0; i--) {
            int mask = ans | (1 << i);
            bool ok = false;

            if ((pre[N] & mask) == mask) {
                ok = true;
            } else if ((pre[N] & mask) == 0) {
                for (int j = 0; j < N; j++) {
                    if ((pre[j + 1] & mask) == mask) {
                        ok = true;
                        break;
                    }
                }
            }

            if (ok)
                ans |= 1 << i;
        }

        cout << ans << '\n';
    }
    return 0;
}
