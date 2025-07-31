#include <bits/stdc++.h>
using namespace std;
int T, n, m, k, t[200001];
bool f[200001];
string s;
int main() {
    for (cin >> T; T; --T) {
        cin >> n >> m >> k >> s;
        s = "L" + s + "L";
        memset(f, 0, sizeof(f));
        f[0] = 1;
        for (int i = 1, las = 0; i < s.size(); i++) {
            if (s[i] != 'L')
                t[i] = las;
            else
                t[i] = las, las = i;
        }
        for (int i = 1; i <= n + 1; i++) {
            if (s[i] == 'C')
                continue;
            if (i - t[i] <= m) {
                f[i] |= f[t[i]];
                if (f[i])
                    continue;
            }
            if (k and f[i - 1])
                k--, f[i] |= f[i - 1];
        }
        cout << (f[n + 1] ? "yEs" : "nO") << '\n';
    }
    return 0;
}
