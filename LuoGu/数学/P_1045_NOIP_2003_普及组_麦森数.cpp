#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int p;
    cin >> p;

    // 位数
    int len = p * log10(2) + 1;

    // 高精度乘法：只保留 555 位
    auto mul = [&](const vector<int> &a, const vector<int> &b) -> vector<int> {
        vector<int> res(600, 0);
        for (int i = 0; i < (int) a.size(); i++) {
            int carry = 0;
            for (int j = 0; j < (int) b.size() && i + j < 600; j++) {
                int cur = res[i + j] + a[i] * b[j] + carry;
                res[i + j] = cur % 10;
                carry = cur / 10;
            }
            if (i + (int) b.size() < 600)
                res[i + b.size()] += carry;
        }
        res.resize(555);
        return res;
    };

    // 快速幂：计算 2^p
    auto q_pow = [&](int a, int e) {
        vector<int> res(1, 1); // 1
        vector<int> A(1, a); // a
        while (e) {
            if (e & 1)
                res = mul(res, A);
            A = mul(A, A);
            e >>= 1;
        }
        return res;
    };

    // 计算 2^p
    auto temp = q_pow(2, p);

    // 减 1（2^p - 1）
    int idx = 0;
    while (idx < (int) temp.size()) {
        if (temp[idx] > 0) {
            temp[idx] -= 1;
            break;
        } else {
            temp[idx] = 9;
            idx++;
        }
    }

    // 输出位数
    cout << len << "\n";

    // 转为字符串（高位 -> 低位）
    string s;
    for (int i = (int) temp.size() - 1; i >= 0; i--) {
        s.push_back(char('0' + temp[i]));
    }

    // 保证 500 位：高位补 0 或截断
    if ((int) s.size() < 500) {
        s = string(500 - (int) s.size(), '0') + s;
    } else if ((int) s.size() > 500) {
        s = s.substr(s.size() - 500);
    }

    // 每行 50 位输出
    for (int i = 0; i < 10; i++) {
        cout << s.substr(i * 50, 50) << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
