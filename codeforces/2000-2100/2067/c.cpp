#include <bits/stdc++.h>
#include <string>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);

void init() {}

void solve() {
    int n;
    cin >> n;

    string s = to_string(n);

    // 如果 n 本身包含 7，直接返回 0
    for (char c: s) {
        if (c == '7') {
            cout << 0 << '\n';
            return;
        }
    }

    auto hasDigit7 = [](long long num) {
        while (num > 0) {
            if (num % 10 == 7)
                return true;
            num /= 10;
        }
        return false;
    };

    int ans = INT_MAX;
    long long power9 = 9;

    // 限制搜索范围，避免超时
    for (int digits = 1; digits <= min(10, (int) s.length() + 1); digits++) {
        long long current = n;

        for (int operations = 1; operations <= 10; operations++) {
            current += power9;
            if (hasDigit7(current)) {
                ans = min(ans, operations);
                break;
            }
        }

        power9 = power9 * 10 + 9; // 9, 99, 999, ...
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
