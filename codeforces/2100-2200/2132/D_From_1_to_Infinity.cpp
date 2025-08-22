#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

int Pow10[18];

void init() {
    Pow10[0] = 1;
    for (int i = 1; i < 18; i++)
        Pow10[i] = 10 * Pow10[i - 1];
}

// 计算 1..n 的位和
int sumDigitsUpTo(int n) {
    if (n < 10)
        return n * (n + 1) / 2;
    string s = to_string(n);
    int len = s.size();
    int first = s[0] - '0';
    int rest = stoll(s.substr(1));
    int sumFirstDigit = first * (first - 1) / 2 * Pow10[len - 1];
    int sumRest = first * (rest + 1);
    return sumFirstDigit + sumRest + sumDigitsUpTo(rest) + (len - 1) * first * 45 * Pow10[len - 2];
}

void solve() {
    int k;
    cin >> k;

    int len = 1, curr = 9;
    while (k > curr * len) {
        k -= curr * len;
        curr *= 10;
        len++;
    }

    int pow10 = 1;
    for (int i = 0; i < len - 1; i++)
        pow10 *= 10;

    int x = (k - 1) / len + pow10;
    string s = to_string(x);
    int need_digits = (k - 1) % len + 1;

    // 先加上 x 的前 need_digits 位
    int ans = 0;
    for (int i = 0; i < need_digits; i++)
        ans += s[i] - '0';

    if (x > 1)
        ans += sumDigitsUpTo(x - 1); // 用数学公式计算 1..x-1 的位和

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
