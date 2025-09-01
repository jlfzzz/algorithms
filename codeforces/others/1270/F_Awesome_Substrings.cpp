#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 5;
const int M = 500 + 5;
const int B = 400;

int pre[N], cnt[N * M];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    s = '#' + s;

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i] == '1');
    }

    i64 ans = 0;
    for (int d = 1; d <= B; d++) {
        for (int i = 0; i <= n; i++) {
            int x = d * pre[i] - i + n;
            ans += cnt[x];
            cnt[x]++;
        }
        for (int i = 0; i <= n; i++) {
            int x = d * pre[i] - i + n;
            cnt[x] = 0;
        }
    }


    for (int d = 1; d <= n / B; d++) {
        for (int i = 1, l = 1, r = 1; i <= n; i++) {
            while (l <= n && pre[l] - pre[i - 1] < d) {
                l++;
            }
            while (r <= n && pre[r] - pre[i - 1] <= d) {
                r++;
            }
            ans += max(0, (r - i) / d - max((l - i) / d, B));
        }
    }
    cout << ans << '\n';

    return 0;
}
